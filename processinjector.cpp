#include "processinjector.h"
#include <algorithm>
#include <stdint.h>
#include <string.h>
#include <windows.h>
#include <tlhelp32.h>

#define EXIT(e) {  CloseHandle(lolProcess); emit injected(InjectionStatus::e); return; }

const unsigned char ProcessInjector::connectcc[] = {
    0x55,										//PUSH EBP
    0x8B, 0xEC,									//MOV EBP, ESP
    0x60, 										//PUSHAD
    0x8B, 0x45, 0x0C, 							//MOV EAX, [EBP+C]
    0x66, 0x83, 0x38, 0x02, 					//CMP WORD PTR [EAX], 2
    0x75, 0x12, 								//JNZ SHORT 12h
    0xB9, 0x08, 0x33, 0x00, 0x00,				//MOV ECX, 3308
    0x66, 0x39, 0x48, 0x02,						//CMP [EAX+2], CX
    0x75, 0x07,									//JNZ SHORT 7h
    0xC7, 0x40, 0x04, 0x7F, 0x00, 0x00, 0x01,	//MOV DWORD PTR [EAX+4], 100007Fh
    0x61,										//POPAD
    0xE9, 0x00, 0x00, 0x00, 0x00				//JMP LONG <X>
};

const unsigned char ProcessInjector::safeCheck[] = {
    0x8B, 0xFF,									//MOVE EDI, EDI
    0x55,										//PUSH EBP
    0x8B, 0xEC									//MOV EBP, ESP
};

ProcessInjector::ProcessInjector(QObject *parent) :
    QThread(parent)
{}

void ProcessInjector::inject()
{
    start(QThread::LowestPriority);
}

void ProcessInjector::run()
{
    HANDLE lolProcess = NULL;
    PROCESSENTRY32 entry;

    // Wait until the client launchs
    do {
        msleep(500);

        entry.dwSize = sizeof(PROCESSENTRY32);
        HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

        if(Process32First(snapshot, &entry)){
            while(Process32Next(snapshot, &entry)){
                if(wcsicmp(entry.szExeFile, L"lolclient.exe") == 0){
                    lolProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, entry.th32ProcessID);

                    if(!lolProcess) { // do this here so we don't close an invalid handle in EXIT
                        CloseHandle(snapshot);
                        emit injected(InjectionStatus::AuthError);
                        exec();
                        return;
                    }

                    break;
                }

            }
        }

        CloseHandle(snapshot);
    } while(!lolProcess);

    //TODO 64bit check

    // Calculate connect function offset
    auto ourWs2 = GetModuleHandleA("ws2_32.dll");
    int32_t offset = (int32_t)GetProcAddress(ourWs2, "connect") - (int32_t)ourWs2;

    // Wait until the client loads ws2
    void* lolConnectAddr = 0;

    do {
        msleep(100);

        MODULEENTRY32 modEntry;
        modEntry.dwSize = sizeof(MODULEENTRY32);
        HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, entry.th32ProcessID);

        if(!snapshot)
            EXIT(MemoryError);

        if(Module32First(snapshot, &modEntry)){
            do{
                if(wcsicmp(modEntry.szModule, L"ws2_32.dll") == 0){
                    lolConnectAddr = modEntry.modBaseAddr + offset;
                    break;
                }
            }while(Module32Next(snapshot, &modEntry));
        }

        CloseHandle(snapshot);
    }while(!lolConnectAddr);

    // Do some checks
    unsigned char checkBuff[5];
    if(!ReadProcessMemory(lolProcess, lolConnectAddr, (void*)checkBuff, 5, NULL))
        EXIT(MemoryError);
    if(checkBuff[0] == 0xe9)
        EXIT(AlreadyInjected);
    if(!std::equal(safeCheck, safeCheck+5, checkBuff))
        EXIT(MemoryError);

    // Create the cc
    LPVOID ccAddr = VirtualAllocEx(lolProcess, NULL, sizeof(connectcc), MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);

    if(!ccAddr)
        EXIT(MemoryError);

    unsigned char cc[sizeof(connectcc)];
    std::copy(connectcc, connectcc+sizeof(cc), cc);

    // Set the jmp back
    *reinterpret_cast<int32_t*>(cc + sizeof(cc)-4) = ((int32_t)lolConnectAddr + 5) - ((int32_t)ccAddr + sizeof(cc));

    if(!WriteProcessMemory(lolProcess, ccAddr, (void*)cc, sizeof(cc), NULL))
        EXIT(MemoryError);

    // Set the jmp in
    unsigned char jmp[5] = {0xe9};
    *reinterpret_cast<int32_t*>(jmp+1) = (int32_t)ccAddr - ((int32_t)lolConnectAddr + 5);

    if(!WriteProcessMemory(lolProcess, lolConnectAddr, jmp, 5, NULL))
        EXIT(MemoryError);

    emit injected(InjectionStatus::Succeed);
}

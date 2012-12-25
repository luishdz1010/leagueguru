#include "processwatcher.h"
#include <windows.h>
#include <tlhelp32.h>

ProcessWatcher::ProcessWatcher(QObject *parent) :
    QThread(parent)
{
}

void ProcessWatcher::run()
{
    HANDLE lolProcess = NULL;
    PROCESSENTRY32 entry;

    entry.dwSize = sizeof(PROCESSENTRY32);
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if(Process32First(snapshot, &entry)){
        while(Process32Next(snapshot, &entry)){
            if(wcsicmp(entry.szExeFile, L"lolclient.exe") == 0){
                lolProcess = OpenProcess(SYNCHRONIZE, FALSE, entry.th32ProcessID);
                WaitForSingleObject(lolProcess, INFINITE);
                CloseHandle(lolProcess);
                break;
            }
        }
    }
    CloseHandle(snapshot);
    emit processClosed();
}

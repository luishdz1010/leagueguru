#ifndef PROCESSINJECTOR_H
#define PROCESSINJECTOR_H

#include <QObject>
#include <QThread>

enum class InjectionStatus{
    Succeed,
    AuthError,
    Unsupported64Bit,
    MemoryError,
    AlreadyInjected
};

/*!
    Injects into the winsocks2 dll of the LoL client to change the connect function in order
    to perform a loopback everytime is called
*/
class ProcessInjector : public QThread
{
    Q_OBJECT
public:
    explicit ProcessInjector(QObject *parent = 0);
    
    /*! Starts the injection process in the background, when the target process starts it
      will try to apply the codecave, the injected signal will be triggered with the result
    */
    void inject();

    /*! Reverts all the changes done to the LoL client */
    //void restore();

signals:
    void injected(InjectionStatus);

protected:
    static const unsigned char connectcc[];
    static const unsigned char safeCheck[];

    void run();
};

#endif // PROCESSINJECTOR_H

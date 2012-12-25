#ifndef PROCESSWATCHER_H
#define PROCESSWATCHER_H

#include <QThread>

/* Watches the lolclient.exe process in a separated thread
 * This class is used to dectect when the lol client closes, so we can close safely. When our client is
 * closed, we don't actually terminate, since doing that will make the client disconnect (due our winsocks2
 * codecabe), instead we create an instance of this class and close as the lol client closes.
 */
class ProcessWatcher : public QThread
{
    Q_OBJECT
public:
    explicit ProcessWatcher(QObject *parent = 0);
    
signals:
    void processClosed();
    
protected:
    void run();
};

#endif // PROCESSWATCHER_H

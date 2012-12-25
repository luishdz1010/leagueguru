#ifndef DATAUPDATER_H
#define DATAUPDATER_H

#include <QObject>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QMap>

class DataUpdater : public QObject
{
    Q_OBJECT
public:
    enum ErrorType{
        NoError,

        NetworkError,
        MissingLocalCatalog,
        CorruptedLocalCatalog,
        CorruptedRemoteCatalog,
        CorruptedFile,
        LocalFileWriteError
    };

    DataUpdater(QUrl remoteUrl, QString localDir, QObject *parent = 0);
    
signals:
    void catalogReady(int files);
    void fileDownloaded();
    void error(DataUpdater::ErrorType);
    
    void finished();

public slots:
    void start();

private slots:
    void catalogReceived();
    void fileReceived();
    void catalogNetworkError(QNetworkReply::NetworkError e);
    void fileNetworkError(QNetworkReply::NetworkError e);

private:
    QMap<QString, QString> parseCatalog(QIODevice* io);

    QNetworkAccessManager net;
    QUrl remoteUrl;
    QString localDir;
    QMap<QNetworkReply*, QString> replyToPathMap;
};

#endif // DATAUPDATER_H

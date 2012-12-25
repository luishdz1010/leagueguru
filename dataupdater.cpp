#include "dataupdater.h"
#include <QNetworkRequest>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include "qslog/QsLog.h"

DataUpdater::DataUpdater(QUrl remoteUrl_, QString localDir_, QObject *parent) :
    QObject(parent),
    remoteUrl(remoteUrl_),
    localDir(localDir_ + '/')
{
}

void DataUpdater::start()
{
    auto reply = net.get(QNetworkRequest(remoteUrl.resolved(QUrl("catalog.txt"))));
    connect(reply, SIGNAL(finished()), this, SLOT(catalogReceived()));
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)),
            this, SLOT(catalogNetworkError(QNetworkReply::NetworkError)));
}

void DataUpdater::catalogReceived()
{
    QNetworkReply* remote = qobject_cast<QNetworkReply*>(sender());
    remote->deleteLater();

    QFile local(localDir + "catalog.txt");

    if(!local.open(QIODevice::ReadWrite | QIODevice::Text)){
        QLOG_ERROR() << "DataUpdater unable to write to local catalog from" << local.fileName();
        emit error(MissingLocalCatalog);
        return;
    }

    int localVersion = local.readLine().trimmed().toInt();
    int remoteVersion = remote->readLine().trimmed().toInt();

    if(localVersion == remoteVersion){
        emit finished();

    } else if(localVersion < remoteVersion){
        auto localReg = parseCatalog(&local);
        if(localReg.isEmpty()){
            QLOG_WARN() << "DataUpdater corrupted local catalog from" << local.fileName();
        }

        auto remoteReg = parseCatalog(remote);
        if(remoteReg.isEmpty()){
            QLOG_ERROR() << "DataUpdater corrupted remote catalog from" << remote->request().url();
            emit error(CorruptedRemoteCatalog);
            return;
        }

        local.reset();
        local.resize(0);
        QTextStream s(&local);
        s << remoteVersion << '\n';

        for(auto it = remoteReg.begin(); it != remoteReg.end(); ++it){
            auto localIt = localReg.find(it.key());

            if(localIt == localReg.end() || localIt.value() != it.value()){
                auto reply = net.get(QNetworkRequest(remoteUrl.resolved(it.key())));

                connect(reply, SIGNAL(finished()), this, SLOT(fileReceived()));
                connect(reply, SIGNAL(error(QNetworkReply::NetworkError)),
                        this, SLOT(fileNetworkError(QNetworkReply::NetworkError)));

                replyToPathMap.insert(reply, it.key());
            }

            s << it.key() << " " << it.value() << '\n';
        }

        emit catalogReady(replyToPathMap.size());

    } else {
        QLOG_ERROR() << "DataUpdater local catalog version is greater than remote";
        emit error(CorruptedLocalCatalog);
    }
}

QMap<QString, QString> DataUpdater::parseCatalog(QIODevice *io)
{
    QMap<QString, QString> ret;

    while(!io->atEnd()){
        auto entry = io->readLine().trimmed().split(' ');

        if(entry.isEmpty())
            continue;

        if(entry.size() < 2 || entry[0].size() < 5)
            return QMap<QString, QString>();

        ret[entry[0]] = entry[1];
    }

    return ret;
}

void DataUpdater::fileReceived()
{
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());
    reply->deleteLater();

    auto relPath = replyToPathMap[reply];
    auto filePath = localDir + relPath;
    replyToPathMap.remove(reply);

    auto data = qUncompress(reply->readAll());
    if(data.isEmpty()){
        QLOG_ERROR() << "DataUpdater failed to uncompress file from" << reply->request().url();
        emit error(CorruptedFile);
        return;
    }

    int lastSep = relPath.lastIndexOf('/');
    if(lastSep != -1)
        QDir(localDir).mkpath(relPath.left(lastSep));

    QFile file(filePath);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Truncate) || file.write(data) == -1){
        QLOG_ERROR() << "DataUpdater unable to write data to" << filePath;
        emit error(LocalFileWriteError);
    } else if(replyToPathMap.isEmpty()){
        emit finished();
    } else {
        emit fileDownloaded();
    }
}

void DataUpdater::catalogNetworkError(QNetworkReply::NetworkError e)
{
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());
    QLOG_WARN() << "DataUpdater failed to retrieve catalog from" << reply->request().url() << "- Error: " << e;
    emit error(NetworkError);
    sender()->deleteLater();
}

void DataUpdater::fileNetworkError(QNetworkReply::NetworkError e)
{
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());
    QLOG_WARN() << "DataUpdater failed to retrieve" << replyToPathMap[reply] << "from" <<
                   reply->request().url() << "- Error: " << e;
    emit error(NetworkError);
    reply->deleteLater();
    replyToPathMap.remove(reply);
}



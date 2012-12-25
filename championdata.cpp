#include "championdata.h"
#include <memory>
#include <QFile>
#include <QDebug>
#include "filepaths.h"
#include "guru/participantrole.pb.h"

bool ChampionDataProvider::addFromFile(QString filepath)
{
    QFile f(filepath);

    if(!f.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    // id,name,role1|role2|role3
    while(!f.atEnd()){
        auto list = f.readLine().split(',');

        if(list.size() < 2)
            continue;

        bool ok;
        std::unique_ptr<ChampionData> cd(new ChampionData());
        cd->id = list[0].toInt(&ok);

        if(!ok)
            return false;

        cd->name = list[1].trimmed();

        if(list.size() < 3)
            continue;

        auto roles = list[2].trimmed().split('|');

        foreach(QByteArray role, roles){
            cd->roles.append(role.toInt(&ok));
            if(!ok || cd->roles.last() < guru::ChampionRole_MIN || cd->roles.last() > guru::ChampionRole_MAX)
                return false;
        }

        int id = cd->id;
        if(championMap.contains(id))
            championMap[id]->roles += cd->roles;
        else
            championMap.insert(id, cd.release());

        auto& storedRoles = championMap[id]->roles;
        storedRoles.resize(std::unique(storedRoles.begin(), storedRoles.end()) - storedRoles.begin());
    }

    return !championMap.empty();
}


ChampionImageProvider::ChampionImageProvider() :
    QDeclarativeImageProvider(QDeclarativeImageProvider::Image),
    invalidImage(":/img/invalidChampion.jpg")
{}

QImage ChampionImageProvider::requestImage(const QString& idStr, QSize *size, const QSize &requestedSize)
{
    bool ok;
    int id = idStr.toInt(&ok);

    if(!ok)
        id = 0;

    auto it = imgCache.find({id, requestedSize});

    if(it != imgCache.end()){
        *size = it->size();
        return *it;
    }

    QImage orgImg;
    if(id == 0 || !orgImg.load(FilePaths::sharedDataLocation() + "/champions/" + idStr + ".jpg")){
        id = 0;
        orgImg = invalidImage;

        // todo try to find the img on the internet
    }

    auto img = orgImg.scaled(requestedSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    if(!img.isNull()){
        *size = img.size();
        imgCache.insert({id, requestedSize}, img);
        return img;
    } else {
        *size = orgImg.size();
        return orgImg;
    }

    return invalidImage;
}

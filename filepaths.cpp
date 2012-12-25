#include "filepaths.h"
#include <QSettings>
#include <QApplication>

QString FilePaths::sharedData;

void FilePaths::init()
{
    QSettings settings(QSettings::IniFormat, QSettings::SystemScope, "abc", "def");
    QString iniFilepath = settings.fileName();
    sharedData = iniFilepath.left(iniFilepath.length() - strlen("abc/def.ini")) + qApp->applicationName();
}

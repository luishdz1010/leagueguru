#include <iostream>
#include <QtGui/QApplication>
#include <QDeclarativeContext>
#include <QtDeclarative>
#include <QFile>
#include <QProcess>
#include <QDesktopServices>
#include "qslog/QsLog.h"
#include "qslog/QsLogDest.h"
#include "filepaths.h"
#include "qmlapplicationviewer.h"
#include "championselectcontroller.h"
#include "gamepacketinspector.h"
#include "processinjector.h"
#include "bansuggestionsmodel.h"
#include "matchparticipantmodel.hpp"
#include "summonerstatsprovider.h"
#include "clientemulator.h"
#include "clientemulatorwindow.h"
#include "championdata.h"
#include "suggestionsfildermodel.h"
#include "rosterfiltermodel.h"
#include "suggestionmodelpickfilter.h"
#include "qmlkeynavigationfix.h"
#include "bootstrap.h"
#include "dataupdater.h"
#include "qtdesktop/qwindowitem.h"

#define APP_VERSION_STR "leagueguru-1.1"
#define APP_VERSION "1.1"

void registerMetaTypes();

int main(int argc, char *argv[])
{
    QScopedPointer<QApplication> app(createApplication(argc, argv));
    app->setWindowIcon(QIcon(":/icon/guru.png"));
    app->setApplicationName("League Guru");
    //app->setOrganizationDomain("leagueguru.net");
    app->setQuitOnLastWindowClosed(false);

    FilePaths::init();

    QsLogging::Logger& logger = QsLogging::Logger::instance();
    logger.setLoggingLevel(QsLogging::TraceLevel);
    QString sLogPath(QDesktopServices::storageLocation(QDesktopServices::DataLocation) + "/log.txt");
    QsLogging::DestinationPtr fileDestination(QsLogging::DestinationFactory::MakeFileDestination(sLogPath));
    QsLogging::DestinationPtr debugDestination(QsLogging::DestinationFactory::MakeDebugOutputDestination());
    logger.addDestination(debugDestination.get());
    logger.addDestination(fileDestination.get());

    registerMetaTypes();

    Bootstrap bootstrap;
    bootstrap.startUpdater();

    return app->exec();
}

void registerMetaTypes()
{
    qRegisterMetaType<InjectionStatus>("InjectionStatus");

    qmlRegisterUncreatableType<Enums>("LeagueGuru", 1, 0, "Enums", "");

    qmlRegisterType<QAbstractItemModel>();

    qmlRegisterInterface<ChampionFilterModel>("ChampionFilterModel");
    qmlRegisterType<SingleChampionFilterModel>();
    qmlRegisterType<MultipleChampionFilterModel>();

    qmlRegisterType<RosterFilterModel>();
    qmlRegisterType<SuggestionsFilderModel>();
    qmlRegisterType<MultipleChampionFilterModel>();

    qmlRegisterType<ParticipantChampionStats>("LeagueGuru", 1, 0, "ParticipantChampionStats");
    qmlRegisterType<SuggestionModelPickFilter>("LeagueGuru", 1, 0, "SuggestionModelPickFilter");
    qmlRegisterType<DeclarativeChampion>("LeagueGuru", 1, 0, "ChampionData");
}

#include "bootstrap.h"
#include "championdata.h"
#include "filepaths.h"
#include "qmlkeynavigationfix.h"
#include "dataupdateview.h"
#include "qslog/QsLog.h"
#include "qtdesktop/qwindowitem.h"
#include <QDeclarativeComponent>
#include <QDeclarativeContext>
#include <QMessageBox>
#include <QDir>


Bootstrap::Bootstrap() :
    component(&engine)
{}

void Bootstrap::startUpdater()
{
    auto updater = new DataUpdater(QUrl("http://dl.dropbox.com/u/118493018/data/"), FilePaths::sharedDataLocation());
    auto updateView = new DataUpdateView();
    updateView->setDataUpdater(updater);

    connect(updater, SIGNAL(finished()), this, SLOT(startApplication()));
    connect(updater, SIGNAL(error(DataUpdater::ErrorType)),
            this, SLOT(onUpdateError(DataUpdater::ErrorType)));
    connect(updater, SIGNAL(finished()), updater, SLOT(deleteLater()));

    updater->start();
    updateView->show();
}

void Bootstrap::onUpdateError(DataUpdater::ErrorType e)
{
    auto updater = qobject_cast<DataUpdater*>(sender());
    updater->deleteLater();
    disconnect(updater, 0, this, 0);

    QMessageBox msg;
    msg.setWindowTitle("League Guru");
    msg.setText("An error ocurred while updating League Guru.");
    msg.setInformativeText("Make sure there are no firewalls blocking outgoing connections from League Guru."
                           " The application will start now. Error code: " + QString::number(e));
    msg.setIcon(QMessageBox::Warning);
    msg.exec();

    startApplication();
}

void Bootstrap::startApplication()
{
    if(!ChampionDataProvider::instance()->addFromFile(FilePaths::sharedDataLocation() + "/champions.csv")){
        QLOG_FATAL() << "missing file champions.csv";
        qApp->exit(-1);
    }

    engine.addImportPath("qmlplugins");
    engine.addImageProvider("champions", new ChampionImageProvider());
    engine.rootContext()->setContextProperty("controller", &controller);

    component.loadUrl(QUrl::fromLocalFile("qml/TeamComp/main.qml"));
    auto rootComponent = component.create();

    if(rootComponent){
        auto window = dynamic_cast<QWindowItem*>(rootComponent);
        window->view()->installEventFilter(new QmlKeyNavigationFix(&engine));
        controller.init();

    } else {
        QLOG_FATAL() << "main.qml component couldn't be created";
        qApp->exit(-1);
    }

    QObject::connect(qApp, SIGNAL(lastWindowClosed()), &localServer, SLOT(kill()));
    QStringList args;
    args << "-datafile" << QDir::toNativeSeparators(FilePaths::sharedDataLocation() + "/championstatsgraph.dat");
    localServer.start("guruserver.exe", args);

    if(!localServer.waitForStarted()){
        QLOG_FATAL() << "guruserver.exe couldn't be started";
        qApp->exit(-1);
    }
}

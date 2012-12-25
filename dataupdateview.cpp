#include "dataupdateview.h"
#include "ui_dataupdateview.h"
#include <QMessageBox>
#include <QDebug>

DataUpdateView::DataUpdateView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DataUpdateView)
{
    ui->setupUi(this);
    ui->updateProgress->setMinimum(0);
}

DataUpdateView::~DataUpdateView()
{
    delete ui;
}

void DataUpdateView::setDataUpdater(DataUpdater *updater)
{
    connect(updater, SIGNAL(catalogReady(int)), ui->updateProgress, SLOT(setMaximum(int)));
    connect(updater, SIGNAL(fileDownloaded()), this, SLOT(incrementProgressBar()));
    connect(updater, SIGNAL(destroyed()), this, SLOT(deleteLater()));
    connect(updater, SIGNAL(error(DataUpdater::ErrorType)),
            this, SLOT(onUpdaterError(DataUpdater::ErrorType)));
}

void DataUpdateView::incrementProgressBar()
{
    ui->updateProgress->setValue(ui->updateProgress->value() + 1);
}

void DataUpdateView::onUpdaterError(DataUpdater::ErrorType e)
{
    disconnect(qobject_cast<DataUpdater*>(sender()), SIGNAL(error(DataUpdater::ErrorType)), this, 0);
    close();
}

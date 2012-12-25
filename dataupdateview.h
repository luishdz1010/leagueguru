#ifndef DATAUPDATEVIEW_H
#define DATAUPDATEVIEW_H

#include <QWidget>
#include "dataupdater.h"

namespace Ui {
class DataUpdateView;
}

class DataUpdateView : public QWidget
{
    Q_OBJECT
    
public:
    explicit DataUpdateView(QWidget *parent = 0);
    ~DataUpdateView();

    void setDataUpdater(DataUpdater* updater);
    
private slots:
    void incrementProgressBar();
    void onUpdaterError(DataUpdater::ErrorType);

private:
    Ui::DataUpdateView *ui;
};

#endif // DATAUPDATEVIEW_H

#ifndef SHOWSERVICEVIEW_H
#define SHOWSERVICEVIEW_H

#include <QtWidgets>
#include "servicemodel.h"

class ShowServiceView : public QTableView
{
    Q_OBJECT

public:
    ShowServiceView( QWidget *parent = 0 );

public slots:
    void setServiceModel();
    void setServiceModel( QString orderId );

private:
    QSharedPointer<ServiceModel> _serviceModel;
};

#endif // SHOWSERVICEVIEW_H

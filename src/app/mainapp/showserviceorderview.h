#ifndef SHOWSERVICEORDERVIEW_H
#define SHOWSERVICEORDERVIEW_H

#include <QtWidgets>
#include "serviceordermodel.h"

class ShowServiceOrderView : public QTableView
{
public:
    ShowServiceOrderView( QWidget *parent = 0 );

    void setServiceOrderModel();

private:
    void message( QString text );

private:
    QSharedPointer<ServiceOrderModel> _serviceOrderModel;
};

#endif // SHOWSERVICEORDERVIEW_H

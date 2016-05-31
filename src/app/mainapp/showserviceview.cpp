#include "showserviceview.h"

ShowServiceView::ShowServiceView( QWidget *parent ) :
    QTableView( parent )
{
    _serviceModel = QSharedPointer<ServiceModel>( new ServiceModel() );
    setServiceModel();
}


void ShowServiceView::setServiceModel()
{
    setModel( _serviceModel->getModel().data() );
    horizontalHeader()->setSectionResizeMode( QHeaderView::Stretch );
    horizontalHeader()->setSectionResizeMode( 0, QHeaderView::ResizeToContents );
    verticalHeader()->hide();
}


void ShowServiceView::setServiceModel( QString orderId )
{
    setModel( _serviceModel->getModel( orderId ).data() );
}

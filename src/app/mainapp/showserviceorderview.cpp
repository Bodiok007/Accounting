#include "showserviceorderview.h"

ShowServiceOrderView::ShowServiceOrderView( QWidget *parent ) :
    QTableView( parent )
{
    _serviceOrderModel = QSharedPointer<ServiceOrderModel>(
                new ServiceOrderModel() );
    setServiceOrderModel();
}


void ShowServiceOrderView::setServiceOrderModel()
{
    auto model = _serviceOrderModel->getModel();

    if ( model->lastError().isValid() ) {
        message( tr( "Помилка при завантаженні послуг!" ) );
        return;
    }

    this->setModel( model.data() );
    horizontalHeader()->setSectionResizeMode( QHeaderView::Stretch );
    horizontalHeader()->setSectionResizeMode( 0, QHeaderView::ResizeToContents );
    horizontalHeader()->setSectionResizeMode( 9, QHeaderView::ResizeToContents );
}


void ShowServiceOrderView::message( QString text )
{
    QMessageBox msgBox;
    msgBox.setText( text );
    msgBox.exec();
}

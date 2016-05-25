#include "serviceorderview.h"

ServiceOrderView::ServiceOrderView( QWidget *parent ) :
    QTableWidget( parent )
{
    setColumnCount(3);
    setHeaders();
    horizontalHeader()->setSectionResizeMode( QHeaderView::Stretch );
}


void ServiceOrderView::setHeaders()
{
    QStringList headers;
    headers << tr( "Категорія" )
            << tr( "Опис" )
            << tr( "Вартість" );

    setHorizontalHeaderLabels( headers );
}

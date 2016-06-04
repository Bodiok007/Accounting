#include "productorderview.h"

ProductOrderView::ProductOrderView( QWidget *parent )
    : QTableWidget( parent )
{ 
    setColumnCount(4);
    setHeaders();
    horizontalHeader()->setSectionResizeMode( QHeaderView::Stretch );
}


void ProductOrderView::setHeaders()
{
    QStringList headers;
    headers << tr( "Назва товару" )
            << tr( "Штрих-код" )
            << tr( "Категорія" )
            << tr( "Вартість одиниці" );

    setHorizontalHeaderLabels( headers );
}

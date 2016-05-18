#include "productorderview.h"

ProductOrderView::ProductOrderView( QWidget *parent )
    : QTableWidget( parent )
{
    setHeaders();
}


void ProductOrderView::setHeaders()
{
    QStringList headers;
    headers << tr( "Назва товару" )
            << tr( "Штрих-код" )
            << tr( "Жанр" )
            << tr( "Кількіть" )
            << tr( "Ціна одиниці" );

    setHorizontalHeaderLabels( headers );
}

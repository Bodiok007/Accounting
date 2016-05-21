#include "productcheck.h"
#include <QDebug>
#include <QtPrintSupport>

ProductCheck::ProductCheck( QObject *parent ) :
    QObject( parent )
{

}


bool ProductCheck::create( QVariant &data )
{
    if ( !data.canConvert<ProductCheckData>() ) {
        logError( this->tr( "Помилка створення чеку на замовлення продуктів" )
                  + data.toString()
                  , __FILE__, __LINE__ );

        return false;
    }

    auto mapContainer = data.value<ProductCheckData>();
    _checkProductList = mapContainer.last();

    QStringList generalList = mapContainer.lastKey();
    _orderId = generalList.at( 0 );
    _employeeName = generalList.at( 1 );

    return true;
}


void ProductCheck::print()
{
    #ifdef QT_DEBUG
        for( Product &product : *_checkProductList ) {
            qDebug() << product.name;
        }
        qDebug() << _orderId;
        qDebug() << _employeeName;;
    #endif

    QString header;
    header = "<head>\n"
                 "<meta Content=\"Text/html; charset=utf-8\">\n"
                 "<style type=\"text/css\">\n"
                     "td {\n"
                         "align: center;\n"
                     "}\n"
                 "</style>\n"
             "</head>";

    QString html = "<html>\n";
    QString endHtml = "</html>\n";

    QString body = "<body bgcolor=#ffffff link=#5000A0>\n";
    QString endBody = "</body>\n";

    QString br = "<br><br><br>\n";

    QString table = "<table width=\"60%\" border=1 cellspacing=0 cellpadding=2>\n";
    QString endTable = "</table>\n";

    QString tableHeader;
    tableHeader = "<tr style=\"background: silver\">\n"
                       "<td colspan='4' align=\"center\" valign=\"middle\">\n"
                           "Замовлення №" + _orderId +
                       "</td>\n"
                   "</tr>\n"
                   "<tr style=\"background: silver\">\n"
                       "<td colspan='2' align=\"center\" valign=\"middle\">\n"
                           "Продавець: " + _employeeName +
                       "</td>\n"
                       "<td colspan='2' align=\"center\" valign=\"middle\">\n"
                            + QDate::currentDate().toString("dd.MM.yyyy") +
                       "</td>\n"
                   "</tr>\n";

    QString tr = "<tr>\n";
    QString endTr = "</tr>\n";

    QString tdColumnHeader = "<td style=\"background: silver\" align=\"center\" valign=\"middle\">\n";
    QString endTdColumnHeader = "</td>\n";

    QString td = "<td align=\"center\" valign=\"middle\">\n";
    QString endTd = "</td>\n";

    QString MP = "М.П. _____";

    QString check = "";
    check += html
              + header
              + body
                  + table
                      + tableHeader;
    check += tr
               + tdColumnHeader
                   + this->tr( "Найменування" )
               + endTdColumnHeader
               + tdColumnHeader
                   + this->tr( "Кількість" )
               + endTdColumnHeader
               + tdColumnHeader
                   + this->tr( "Ціна одиниці" )
               + endTdColumnHeader
               + tdColumnHeader
                   + this->tr( "Сума" )
               + endTdColumnHeader
           + endTr;

    double sum = 0;
    double currentSum = 0;

    for( Product &product : *_checkProductList ) {
        currentSum = product.count.toDouble() * product.cost.toDouble();
        sum += currentSum;

        check += tr
                  + td
                      + product.name
                  + endTd
                  + td
                      + product.count
                  + endTd
                  + td
                      + product.cost
                  + endTd
                  + td
                      + QString::number( currentSum )
                  + endTd
              + endTr;
    }

    check += tr
               + "<td colspan='4' align=\"right\" valign=\"middle\"> \n"
               + "Всього: " + QString::number( sum )
               + endTd
           + endTr;

    check += endTable
           + br
           + MP;

    check     += endBody
          + endHtml
          + br;

    check += check;

    QTextDocument document;
    document.setHtml( check );

    QPrinter printer;
    QPrintDialog dialog( &printer );

    if ( dialog.exec() == QDialog::Accepted ) {
        document.print( &printer );
    }
    else {
        logError( this->tr( "Друк не підтверджено" ), __FILE__, __LINE__ );
    }
}


void ProductCheck::logError( QString message, QString fileName, int line )
{
    ErrorFileInfo fileInfo;
    fileInfo.setFileName( fileName );
    fileInfo.setLine( line );

    Logger::getInstance()->log( ErrorType::ERRORR
                                , message
                                , fileInfo );
}

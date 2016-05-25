#include "servicecheck.h"
#include <QDebug>
#include <QDate>
#include <QtPrintSupport>

ServiceCheck::ServiceCheck( QObject *parent ) :
    QObject( parent )
{

}


bool ServiceCheck::create( QVariant &data )
{
    if ( !data.canConvert<ServiceCheckData>() ) {
        logError( this->tr( "Помилка створення чеку на замовлення послуг" )
                  + data.toString()
                  , __FILE__, __LINE__ );

        return false;
    }

    auto mapContainer = data.value<ServiceCheckData>();
    _checkServiceList = mapContainer.last();

    QStringList generalList = mapContainer.lastKey();
    _orderId = generalList.at( 0 );
    _employeeName = generalList.at( 1 );
    _customerName = generalList.at( 2 );

    return true;
}


void ServiceCheck::print()
{
    #ifdef QT_DEBUG
        for( Service &service : *_checkServiceList ) {
            qDebug() << service.description;
        }
        qDebug() << _orderId;
        qDebug() << _employeeName;
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
    tableHeader =
        "<tr style=\"background: silver\">\n"
            "<td colspan='4' align=\"center\" valign=\"middle\">\n"
                "Замовлення №" + _orderId +
            "</td>\n"
        "</tr>\n"
        "<tr style=\"background: silver\">\n"
            "<td colspan='2' align=\"center\" valign=\"middle\">\n"
                "Працівник: " + _employeeName +
            "</td>\n"
            "<td colspan='2' rowspan='2' align=\"center\" valign=\"middle\">\n"
                 + QDate::currentDate().toString("dd.MM.yyyy") +
            "</td>\n"
        "</tr>\n"
        "<tr style=\"background: silver\">\n"
            "<td colspan='2' align=\"center\" valign=\"middle\">\n"
                "Замовник: " + _customerName +
            "</td>\n"
        "</tr>\n";

    QString tr = "<tr>\n";
    QString endTr = "</tr>\n";

    QString tdColumnHeader =
        "<td colspan='2' style=\"background: silver\" align=\"center\" valign=\"middle\">\n";
    QString endTdColumnHeader = "</td>\n";

    QString td = "<td colspan='2' align=\"center\" valign=\"middle\">\n";
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
                   + this->tr( "Опис" )
               + endTdColumnHeader
               + tdColumnHeader
                   + this->tr( "Вартість" )
               + endTdColumnHeader
           + endTr;

    double sum = 0;

    for( Service &service : *_checkServiceList ) {
        sum += service.cost.toDouble();

        check += tr
                  + td
                      + service.description
                  + endTd
                  + td
                      + service.cost
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


void ServiceCheck::logError( QString message, QString fileName, int line )
{
    ErrorFileInfo fileInfo;
    fileInfo.setFileName( fileName );
    fileInfo.setLine( line );

    Logger::getInstance()->log( ErrorType::ERRORR
                                , message
                                , fileInfo );
}

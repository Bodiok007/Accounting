#include "mainwindow.h"
#include "loginform.h"
#include <QApplication>
#include "adminform.h"
#include "addemployeeform.h"
#include "mainapp.h"
#include "mainwindow.h"
#include "productorderview.h"
#include "productform.h"
#include "saleform.h"
#include "customerform.h"
#include "addserviceform.h"
#include "serviceorderform.h"
#include "showserviceorderform.h"

int main(int argc, char *argv[])
{
    QApplication app( argc, argv );
    /*LoginForm w;
    w.show();
    AdminForm af;
    af.show();

    QString p = "1111";
    QByteArray pass( p.toStdString().c_str() );
    QString blah = QString(QCryptographicHash::hash((pass),QCryptographicHash::Sha256).toHex());
    qDebug() << blah;*/
    /*ProductOrderView prd;
    prd.show();*/
    MainApp mainApp;
    QString date = QDate::currentDate().toString( QString("yyyy-MM-dd") );

    /*ShowServiceOrderForm ssof;
    ssof.show();*/

    /*ServiceOrderForm sof;
    sof.show();*/

    /*CustomerForm cf;
    cf.show();*/

    /*ProductOrderForm pof;
    pof.show();*/

    /*ProductForm pf;
    pf.show();*/

    /*MainWindow mw;
    mw.show();*/

    /*auto db = Db::getInstance();

    bool ok = db->transaction();
    qDebug() << ok;

    if ( db->lastError().isValid() ) {
        qDebug() << "Begin transaction error" << db->lastError().text();
    }
    //db->query( "INSERT INTO product(productCategoryId, name, cost, barcode) VALUES(1, 'SAMSUNG LS24D300HSI (LS24D300HSI/CI)', 3000, 1234 )" );
    db->query( "select addOr('1', '" + date +"')" );
    //db->query( "call getLastInsetId()" );
    qDebug() << db->lastInsertId().toString();

    auto query = db->getData();

    while (query->next()) {
        qDebug() << query->value(0).toString() << " ";
    }*/

    /*db->getData()->next();
    qDebug() << db->getData()->lastInsertId().toString();*/
    /*db->rollback();
    if ( db->lastError().isValid() ) {
        qDebug() << "Rollback transaction error" << db->lastError().text();
    }*/

    //db->connectToDb();
    /*bool statusOk = db->transaction();
    qDebug() << statusOk;
    if ( !statusOk ) {
        qDebug() << "Transaction error" << db->lastError().text();
    }
    db->query( "call getEmployee() " );
    statusOk = db->rollback();
    if ( !statusOk ) {
        qDebug() << "Rollback error" << db->lastError().text();
    }*/

    /*auto db =  QSqlDatabase::addDatabase( "QMYSQL" );

    db.setDatabaseName( "accounting" );
    db.setUserName( "root" );
    db.setHostName( "localhost" );
    db.setPassword( "1111" );

    if ( !db.open() )
    {
        qDebug() << db.lastError().text();
    }

    if (db.driver()->beginTransaction()) {
        qDebug() << "OK";
    }
    db.exec("INSERT INTO product(productCategoryId, name, cost, barcode) VALUES(1, 'Prod', 10, 1234 )");
    if (db.lastError().isValid()) {
        qDebug() << db.lastError().text();
    }
    db.driver()->rollbackTransaction();
    if ( !db.transaction() ) {
        qDebug() << db.lastError().text() << "NOOOOO1";
    }*/

    /*auto Db::getInstance()->
    qDebug() << db.transaction();*/

    QStyle* pstyle = QStyleFactory::create("Fusion");
    QApplication::setStyle( pstyle );

    return app.exec();
}

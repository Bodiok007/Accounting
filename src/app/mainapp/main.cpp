#include "mainwindow.h"
#include "loginform.h"
#include <QApplication>
#include "adminform.h"
#include "addemployeeform.h"
#include "mainapp.h"
#include "mainwindow.h"
#include "productorderview.h"

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
    qDebug() << QDate::currentDate().toString( QString("yyyy-MM-dd") );
    /*MainWindow mw;
    mw.show();*/

    /*auto Db::getInstance()->
    qDebug() << db.transaction();*/

    QStyle* pstyle = QStyleFactory::create("Fusion");
    QApplication::setStyle( pstyle );

    return app.exec();
}

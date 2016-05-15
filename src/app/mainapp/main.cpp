#include "mainwindow.h"
#include "loginform.h"
#include <QApplication>
#include "adminform.h"
#include "addemployeeform.h"

int main(int argc, char *argv[])
{
    QApplication app( argc, argv );
    LoginForm w;
    w.show();
    AdminForm af;
    af.show();
    AddEmployeeForm aef;
    aef.show();
    QString p = "1111";
    QByteArray pass( p.toStdString().c_str() );
    QString blah = QString(QCryptographicHash::hash((pass),QCryptographicHash::Sha256).toHex());
    qDebug() << blah;

    QStyle* pstyle = QStyleFactory::create("Fusion");
    QApplication::setStyle( pstyle );

    return app.exec();
}

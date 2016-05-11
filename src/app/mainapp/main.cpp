#include "mainwindow.h"
#include "loginform.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginForm w;
    w.show();

    QStyle* pstyle = QStyleFactory::create("Fusion");
    QApplication::setStyle(pstyle);

    return a.exec();
}

#include "mainwindow.h"
#include "loginform.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    LoginForm w;
    w.show();

    QStyle* pstyle = QStyleFactory::create("Fusion");
    QApplication::setStyle(pstyle);

    return app.exec();
}

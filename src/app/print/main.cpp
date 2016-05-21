#include <QApplication>
#include "declaremetatype.h"
#include "productcheck.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Product data1;
    data1.name = "Monitor";
    data1.cost = "3455";
    data1.count = "1";

    Product data2;
    data2.name = "Monitor2";
    data2.cost = "2455";
    data2.count = "2";

    QList<Product> data;
    data.append( data1 );
    data.append( data2 );


    //container
    QStringList general;
    general << "1" << "Mazurok Vitaliy";

    ProductCheckData map; map[ general ] = &data;
    QVariant toCheckContainer;
    toCheckContainer.setValue( map );

    ProductCheck check;
    check.create( toCheckContainer );
    check.print();


    return a.exec();
}

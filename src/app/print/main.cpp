#include <QApplication>
#include "declaremetatype.h"
#include "productcheck.h"
#include <QDebug>
#include "checkmanager.h"
#include "servicecheck.h"

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
    /*QStringList general;
    general << "1" << "Mazurok Vitaliy";*/

    /*ProductCheckData map; map[ general ] = &data;
    QVariant toCheckContainer;
    toCheckContainer.setValue( map );*/

    /*CheckManager manager( nullptr, new ProductCheck() );
    manager.create( toCheckContainer );
    manager.print();*/

    /*********************************************************/

    Service service1;
    service1.description = "Description! More and more decription in your hand! For infinity";
    service1.cost = "320";

    Service service2;
    service2.description = "Description2";
    service2.cost = "220";

    QStringList general;
    general << "1" << "Mazurok Vitaliy" << "Some customer";

    QList<Service> serviceList;
    serviceList.append( service1 );
    serviceList.append( service2 );

    ServiceCheckData map;
    map[ general ] = &serviceList;
    QVariant toCheckContainer;
    toCheckContainer.setValue( map );

    CheckManager manager( nullptr, new ServiceCheck() );
    manager.create( toCheckContainer );
    manager.print();

    /*ProductCheck check;
    check.create( toCheckContainer );
    check.print();*/


    return a.exec();
}

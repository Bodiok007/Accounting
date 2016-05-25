#ifndef PRODUCTCHECKDATA_H
#define PRODUCTCHECKDATA_H

#include <QMetaType>
#include "../mainapp/product.h"
#include "../mainapp/service.h"


Q_DECLARE_METATYPE( Product )
Q_DECLARE_METATYPE( Product* )
Q_DECLARE_OPAQUE_POINTER( Product* )

Q_DECLARE_OPAQUE_POINTER( QList<Product> *)

typedef QMap<QStringList, QList<Product>*> ProductCheckData;
Q_DECLARE_METATYPE(ProductCheckData)


Q_DECLARE_METATYPE( Service )
Q_DECLARE_METATYPE( Service* )
Q_DECLARE_OPAQUE_POINTER( Service* )

Q_DECLARE_OPAQUE_POINTER( QList<Service> *)

typedef QMap<QStringList, QList<Service>*> ServiceCheckData;
Q_DECLARE_METATYPE(ServiceCheckData)

#endif // PRODUCTCHECKDATA_H

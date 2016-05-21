#ifndef PRODUCTCHECKDATA_H
#define PRODUCTCHECKDATA_H

#include <QMetaType>
#include "../mainapp/product.h"


Q_DECLARE_METATYPE( Product )
Q_DECLARE_METATYPE( Product* )
Q_DECLARE_OPAQUE_POINTER( Product* )

Q_DECLARE_OPAQUE_POINTER( QList<Product> *)

typedef QMap<QStringList, QList<Product>*> ProductCheckData;
Q_DECLARE_METATYPE(ProductCheckData)


#endif // PRODUCTCHECKDATA_H

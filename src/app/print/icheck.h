#ifndef ICHECK_H
#define ICHECK_H

#include "iprint.h"
#include <QVariant>

class ICheck : public IPrint
{
public:
    virtual ~ICheck() {}
    virtual bool create( QVariant &data ) = 0;
};

#endif // ICHECK_H

#include "checkmanager.h"

CheckManager::CheckManager( QObject *parent, ICheck *check ) :
    QObject( parent )
{
    _check = QSharedPointer<ICheck>( check );
}


bool CheckManager::create( QVariant &data )
{
    bool statusOk = _check->create( data );
    return statusOk;
}


void CheckManager::print()
{
    _check->print();
}

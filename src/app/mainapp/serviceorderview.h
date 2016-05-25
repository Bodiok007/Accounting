#ifndef SERVICEORDERVIEW_H
#define SERVICEORDERVIEW_H

#include <QtWidgets>

class ServiceOrderView : public QTableWidget
{
    Q_OBJECT

public:
    ServiceOrderView( QWidget *parent = 0 );

private:
    void setHeaders();
};

#endif // SERVICEORDERVIEW_H

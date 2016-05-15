#ifndef EMPLOYEETABLEVIEW_H
#define EMPLOYEETABLEVIEW_H

#include <QtWidgets>
#include "usermodel.h"

class EmployeeTableView : public QTableView
{
    Q_OBJECT

public:
    EmployeeTableView( QWidget *parent);

public slots:
    void setEmployeeModel();

private:
    void message( QString text );

private:
    QSharedPointer<UserModel> _model;
};

#endif // EMPLOYEETABLEVIEW_H

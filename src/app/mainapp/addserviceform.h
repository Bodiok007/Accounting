#ifndef ADDSERVICEFORM_H
#define ADDSERVICEFORM_H

#include <QWidget>
#include "servicemodel.h"
#include "customermodel.h"
#include "addcustomerform.h"
#include "service.h"
#include "customer.h"

namespace Ui {
class AddServiceForm;
}

class AddServiceForm : public QWidget
{
    Q_OBJECT

public:
    explicit AddServiceForm( QWidget *parent = 0 );
    ~AddServiceForm();

signals:
    void addService( Service & );

private:
    void initFields();
    void connectSlots();
    bool isEmpty( Service &service );
    void clearFields();
    void message( QString text );

private slots:
    void saveService();

private:
    Ui::AddServiceForm *ui;
    QSharedPointer<ServiceModel> _serviceModel;
    QSharedPointer<Db> _db;
};

#endif // ADDSERVICEFORM_H

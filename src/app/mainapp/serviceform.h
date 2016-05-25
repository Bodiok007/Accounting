#ifndef SERVICEFORM_H
#define SERVICEFORM_H

#include <QWidget>

namespace Ui {
class ServiceForm;
}

class ServiceForm : public QWidget
{
    Q_OBJECT

public:
    explicit ServiceForm( QWidget *parent = 0 );
    ~ServiceForm();

private:
    Ui::ServiceForm *ui;
};

#endif // SERVICEFORM_H

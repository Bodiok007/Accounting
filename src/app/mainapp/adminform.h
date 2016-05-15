#ifndef ADMINFORM_H
#define ADMINFORM_H

#include <QWidget>
#include "messagemodel.h"

namespace Ui {
class AdminForm;
}

class AdminForm : public QWidget
{
    Q_OBJECT

public:
    explicit AdminForm(QWidget *parent = 0);
    ~AdminForm();

private:
    Ui::AdminForm *ui;
};

#endif // ADMINFORM_H

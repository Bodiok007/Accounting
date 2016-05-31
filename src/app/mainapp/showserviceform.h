#ifndef SHOWSERVICEFORM_H
#define SHOWSERVICEFORM_H

#include <QWidget>

namespace Ui {
class ShowServiceForm;
}

class ShowServiceForm : public QWidget
{
    Q_OBJECT

public:
    explicit ShowServiceForm(QWidget *parent = 0);
    ~ShowServiceForm();

private:
    Ui::ShowServiceForm *ui;
};

#endif // SHOWSERVICEFORM_H

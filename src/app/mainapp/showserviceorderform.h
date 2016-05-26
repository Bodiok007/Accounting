#ifndef SHOWSERVICEORDERFORM_H
#define SHOWSERVICEORDERFORM_H

#include <QWidget>

namespace Ui {
class ShowServiceOrderForm;
}

class ShowServiceOrderForm : public QWidget
{
    Q_OBJECT

public:
    explicit ShowServiceOrderForm(QWidget *parent = 0);
    ~ShowServiceOrderForm();

signals:
    void closeShowServiceOrderForm();

protected:
    void closeEvent( QCloseEvent *event );

private:
    Ui::ShowServiceOrderForm *ui;
};

#endif // SHOWSERVICEORDERFORM_H

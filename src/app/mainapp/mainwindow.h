#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "saleorderform.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow( QWidget *parent = 0 );

signals:
    void closeMainForm();

protected:
    void closeEvent( QCloseEvent *event );

private slots:
    void emitClose();

    void createSaleOrderForm();
    void showSaleOrderForm();
    void destroySaleOrderForm();

private:
    void connectSlots();

private:
    Ui::MainWindow *ui;
    QSharedPointer<SaleOrderForm> _saleOrderForm;
};

#endif // MAINWINDOW_H

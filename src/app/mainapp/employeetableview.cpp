#include "employeetableview.h"

EmployeeTableView::EmployeeTableView( QWidget *parent )
    : QTableView( parent )
{
    _model = QSharedPointer<UserModel>( new UserModel() );
}


void EmployeeTableView::setEmployeeModel()
{
    auto model = _model->getModel();

    if ( model->lastError().isValid() ) {
        message( tr( "Помилка при завантаженні працівників!" ) );
        return;
    }
    this->setModel( &*model );
    this->setColumnHidden( 0, true );

    horizontalHeader()->setSectionResizeMode( 0, QHeaderView::Stretch );
    horizontalHeader()->setSectionResizeMode( 1, QHeaderView::Stretch );
    horizontalHeader()->setSectionResizeMode( 2, QHeaderView::Stretch );
}


void EmployeeTableView::message( QString text )
{
    QMessageBox msgBox;
    msgBox.setText( text );
    msgBox.exec();
}

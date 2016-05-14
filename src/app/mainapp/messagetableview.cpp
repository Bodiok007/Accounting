#include "messagetableview.h"

MessageTableView::MessageTableView( QWidget *parent )
    : QTableView( parent )
{
    _model = QSharedPointer<MessageModel>( new MessageModel() );
}


void MessageTableView::setMessageModel()
{
    auto model = _model->getModel();

    if ( model->lastError().isValid() ) {
        message( tr( "Помилка при завантаженні повідомлень!" ) );
        return;
    }

    this->setModel( _model->getModel() );
}


void MessageTableView::message( QString text )
{
    QMessageBox msgBox;
    msgBox.setText( text );
    msgBox.exec();
}

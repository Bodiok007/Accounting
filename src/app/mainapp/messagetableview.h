#ifndef MESSAGETABLEVIEW_H
#define MESSAGETABLEVIEW_H

#include <QtWidgets>
#include "messagemodel.h"

class MessageTableView : public QTableView
{
    Q_OBJECT

public:
    MessageTableView( QWidget *parent = 0 );

public slots:
    void setMessageModel();

private:
    QSharedPointer<MessageModel> _model;

private:
    void message( QString text );
};

#endif // MESSAGETABLEVIEW_H

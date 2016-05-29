#include <QApplication>
#include "smssetting.h"
#include <QDebug>
#include "smsclubservice.h"
#include "responceparser.h"
#include <QMessageBox>
#include "smsmanager.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SmsClubService scs;
    scs.getStatusRequest( "273241119" );
    //scs.send("324324", "sdfsd");
    /*QMessageBox msg;
    while (1) {
        qDebug() << scs.getStatus();
        msg.exec();

    }*/

    SmsManager *manager = new SmsManager( nullptr, new SmsClubService() );
    manager->getStatusRequest( "273241119" );
    QMessageBox msg;
    while (1) {
        qDebug() << manager->getStatus();
        msg.exec();

    }

    delete manager;

    //scs.send("234324", "Замовлення №346 готове! З повагою, магазин «Комп'ютерна техніка»!");
    /*SmsSettingData st;
        qDebug() << "default" << st.isError;
        st.login = "325432524";
        st.password = "dsf";
        st.alfaName = "alfa";
    scs.setSetting( std::move( st ) );*/

    //qDebug() << scs.getEncodedMessage( "sdfds" ).toBase64();
    /*SmsSetting stng;
    stng.*/

    /*SmsSettingData st;
    qDebug() << "default" << st.isError;
    st.login = "325432524";
    st.password = "dsf";
    st.alfaName = "alfa";*/

    /*SmsSettingData data = stng.readSetting();
    qDebug() << data.login << " "
             << data.password << " "
             << data.isError;*/

   /* QString message = "=IDS START=<br/>273241119: 2165-05-28 21:14:21<br/>=IDS END=<br/>";
    QString message2 = "=IDS START=<br/>273241119<br/>=IDS END=";/*/
    //ResponseParser rp;
    //qDebug() << rp.getStatus( message );
    //rp.getMessageId( message2 );
    return a.exec();
}

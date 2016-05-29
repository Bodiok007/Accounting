#-------------------------------------------------
#
# Project created by QtCreator 2016-05-11T13:43:26
#
#-------------------------------------------------

QT       += core gui sql printsupport network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mainapp
TEMPLATE = app

CONFIG += c++14

SOURCES += main.cpp \
    mainapp.cpp

HEADERS  += querytype.h \
    mainapp.h


FORMS += \
    loginform.ui \
    adminform.ui \
    addemployeeform.ui \
    editemployeeform.ui \
    changepasswordform.ui \
    mainwindow.ui \
    saleorderform.ui \
    addproductform.ui \
    productform.ui \
    customerform.ui \
    addcustomerform.ui \
    saleform.ui \
    serviceform.ui \
    serviceorderform.ui \
    addserviceform.ui \
    showserviceorderform.ui \
    editcustomerform.ui \
    messagesettingform.ui

RESOURCES += \
    resource.qrc

include(loginform.pri)
include(admin.pri)
include(models.pri)
include(views.pri)
include(mainwindow.pri)
include(sale.pri)
include(product.pri)
include(customer.pri)
include(service.pri)

INCLUDEPATH += ../log
LIBS += -llog

INCLUDEPATH += ../db
LIBS += -ldb

INCLUDEPATH += ../print
LIBS += -lprint

INCLUDEPATH += ../sms
LIBS += -lsms


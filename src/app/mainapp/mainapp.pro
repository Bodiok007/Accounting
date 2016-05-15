#-------------------------------------------------
#
# Project created by QtCreator 2016-05-11T13:43:26
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mainapp
TEMPLATE = app

CONFIG += c++14

SOURCES += main.cpp\
        mainwindow.cpp


HEADERS  += mainwindow.h \
    querytype.h


FORMS += \
    loginform.ui \
    adminform.ui \
    addemployeeform.ui

RESOURCES += \
    resource.qrc

include(loginform.pri)
include(admin.pri)
include(models.pri)
include(views.pri)

INCLUDEPATH += ../log
LIBS += -llog

INCLUDEPATH += ../db
LIBS += -ldb


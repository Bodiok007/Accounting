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
    loginform.ui

RESOURCES += \
    resource.qrc

include(loginform.pri)

#include(../db/db.pri)
#INCLUDEPATH += ../db/

#include(../log/logger.pri)
INCLUDEPATH += ../log
LIBS += -llog

INCLUDEPATH += ../db
LIBS += -ldb
#INCLUDEPATH += ../../../build/src/app/db/debu
#include(../../../build/src/app/db/debug)


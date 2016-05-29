#-------------------------------------------------
#
# Project created by QtCreator 2016-05-27T18:39:23
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = sms
TEMPLATE = app

CONFIG += c++14

SOURCES += main.cpp


HEADERS  +=

include(smsservice.pri)

INCLUDEPATH += ../log
LIBS += -llog

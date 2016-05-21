#-------------------------------------------------
#
# Project created by QtCreator 2016-05-21T14:15:51
#
#-------------------------------------------------

QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = print
TEMPLATE = app

CONFIG += c++14

SOURCES += main.cpp

HEADERS  +=

include(printcheck.pri)

INCLUDEPATH += ../log
LIBS += -llog

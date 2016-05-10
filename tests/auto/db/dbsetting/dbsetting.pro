#-------------------------------------------------
#
# Project created by QtCreator 2016-05-07T12:47:12
#
#-------------------------------------------------

QT       += testlib

QT       += core gui widgets sql

TARGET = tst_dbsetting
#CONFIG   += console
#CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_dbsetting.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

include(../../../../src/app/db/db.pri)
INCLUDEPATH += ../../../../src/app/db/

include(../../../../src/app/log/logger.pri)
INCLUDEPATH += ../../../../src/app/log/

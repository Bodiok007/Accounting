#-------------------------------------------------
#
# Project created by QtCreator 2016-05-05T16:58:43
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_errorfileinfo
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_errorfileinfo.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

include(../../../../src/app/log/logger.pri)
INCLUDEPATH += ../../../../src/app/log/

#-------------------------------------------------
#
# Project created by QtCreator 2016-05-05T14:29:05
#
#-------------------------------------------------

QT       += testlib

QT       += gui

TARGET = tst_logtofiletest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += \
    tst_logtofile.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

include(../../../../src/app/log/logger.pri)
INCLUDEPATH += ../../../../src/app/log/

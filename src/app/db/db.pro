#-------------------------------------------------
#
# Project created by QtCreator 2016-05-03T22:39:32
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = db
TEMPLATE = lib

CONFIG += c++14

SOURCES +=


HEADERS  +=

include(db.pri)
include(../log/logger.pri)
INCLUDEPATH += ../log/

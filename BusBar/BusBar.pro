#-------------------------------------------------
#
# Project created by QtCreator 2017-05-23T17:48:22
#
#-------------------------------------------------

QT       += core gui

TARGET = BusBar
TEMPLATE = app

include(test/test.pri)
include(common/common.pri)
include(modbus/modbus.pri)

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

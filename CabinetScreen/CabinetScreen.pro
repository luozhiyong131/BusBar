#-------------------------------------------------
#
# Project created by QtCreator 2017-11-08T17:13:55
#
#-------------------------------------------------

QT       += core gui
QT       += sql
QT       += network
#QT       += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CabinetScreen
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

include(common/common.pri)
include(net/net.pri)
include(services/services.pri)
include(home/home.pri)
include(logs/logs.pri)
include(setting/setting.pri)
include(dp/dp.pri)
include(sql/sql.pri)

SOURCES += \
        main.cpp \
        mainwindow.cpp

HEADERS += \
        mainwindow.h

FORMS += \
        mainwindow.ui

target.path = /opt
INSTALLS += target

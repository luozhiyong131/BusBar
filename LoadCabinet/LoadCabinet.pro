#-------------------------------------------------
#
# Project created by QtCreator 2018-08-09T10:01:24
#
#-------------------------------------------------

QT       += core gui
QT       += sql
QT       += network
#QT       += charts
#QT       += websockets
#QT       += printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LoadCabinet
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
include(input/input.pri)
include(eload/eload.pri)

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    home/h_mainwid.cpp \
    home/e_statushomewid.cpp \
    home/e_inputunitwid.cpp \
    home/e_inputhomewid.cpp

HEADERS += \
        mainwindow.h \
    home/h_mainwid.h \
    home/e_statushomewid.h \
    home/e_inputunitwid.h \
    home/e_inputhomewid.h

FORMS += \
        mainwindow.ui \
    home/h_mainwid.ui \
    home/e_statushomewid.ui \
    home/e_inputunitwid.ui \
    home/e_inputhomewid.ui

RESOURCES += \
    images/image.qrc

target.path = /opt
INSTALLS += target



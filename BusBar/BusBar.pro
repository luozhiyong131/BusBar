#-------------------------------------------------
#
# Project created by QtCreator 2017-05-23T17:48:22
#
#-------------------------------------------------

QT      += core gui
QT      += widgets printsupport
QT      += sql
QT      += network

TARGET = BusBar
TEMPLATE = app

include(test/test.pri)
include(common/common.pri)
include(modbus/modbus.pri)
include(sql/sql.pri)
include(dp/dp.pri)
include(home/home.pri)
include(line/line.pri)
include(branch/branch.pri)
include(logs/logs.pri)
include(setting/setting.pri)
include(services/services.pri)
include(shm/shm.pri)

SOURCES += main.cpp\
        mainwindow.cpp \
    currentalarmsdlg.cpp

HEADERS  += mainwindow.h \
    currentalarmsdlg.h

FORMS    += mainwindow.ui \
    currentalarmsdlg.ui

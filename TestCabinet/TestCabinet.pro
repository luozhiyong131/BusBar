#-------------------------------------------------
#
# Project created by QtCreator 2017-09-25T19:01:21
#
#-------------------------------------------------

QT       += core gui network  sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TestCabinet
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

INCLUDEPATH +=  serialport \
                                    modbus \
                                    total \
                                    output \
                                    fieldvalues \
                                    sensor \
                                    sql \
                                    logs \
                                    alarm \
                                    datetime \
                                    common \
                                    partswidget \

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    common/common.cpp \
    datetime/timesettingdlg.cpp \
    serialport/serial_portset.cpp \
    serialport/serial_test.cpp \
    serialport/serial_trans.cpp \
    sql/db_sqlquery.cpp \
    sql/db_sqltablemodel.cpp \
    modbus/mdb_corethread.cpp \
    modbus/mdb_readthread.cpp \
    modbus/mdb_recvcmd.cpp \
    modbus/mdb_sentcmd.cpp \
    modbus/mdb_writecmd.cpp \
    modbus/mdb_writethread.cpp \
    alarm/alarm_thread.cpp \
    total/total_maindlg.cpp \
    total/total_thresholddlg.cpp \
    total/total_thresholdset.cpp \
    total/total_waitdlg.cpp \
    fieldvalues/fv_maindlg.cpp \
    fieldvalues/fv_setdlg.cpp \
    fieldvalues/fv_tablewidget.cpp \
    fieldvalues/fv_thresholddlg.cpp \
    fieldvalues/fv_waitdlg.cpp \
    output/op_outputdlg.cpp \
    output/op_tablewidget.cpp \
    logs/log_showdlg.cpp \
    logs/log_tableview.cpp \
    ctoolbutton.cpp \
    common/msgbox.cpp

HEADERS += \
        mainwindow.h \
    common/common.h \
    datetime/timesettingdlg.h \
    serialport/Serial_PortData.h \
    serialport/serial_portset.h \
    serialport/serial_test.h \
    serialport/serial_trans.h \
    sql/db_sqlquery.h \
    sql/db_sqltablemodel.h \
    modbus/mdb_corethread.h \
    modbus/mdb_npmvdef.h \
    modbus/mdb_npmvtype.h \
    modbus/mdb_readthread.h \
    modbus/mdb_recvcmd.h \
    modbus/mdb_sentcmd.h \
    modbus/mdb_writecmd.h \
    modbus/mdb_writethread.h \
    alarm/alarm_thread.h \
    total/total_maindlg.h \
    total/total_thresholddlg.h \
    total/total_thresholdset.h \
    total/total_waitdlg.h \
    fieldvalues/fv_maindlg.h \
    fieldvalues/fv_setdlg.h \
    fieldvalues/fv_tablewidget.h \
    fieldvalues/fv_thresholddlg.h \
    fieldvalues/fv_waitdlg.h \
    output/op_outputdlg.h \
    output/op_tablewidget.h \
    logs/log_showdlg.h \
    logs/log_tableview.h \
    ctoolbutton.h \
    common/msgbox.h

FORMS += \
        mainwindow.ui \
    datetime/timesettingdlg.ui \
    total/total_maindlg.ui \
    total/total_thresholddlg.ui \
    total/total_thresholdset.ui \
    total/total_waitdlg.ui \
    fieldvalues/fv_maindlg.ui \
    fieldvalues/fv_setdlg.ui \
    fieldvalues/fv_thresholddlg.ui \
    fieldvalues/fv_waitdlg.ui \
    output/op_outputdlg.ui \
    logs/log_showdlg.ui

RESOURCES += \
    image/image.qrc


target.path = /opt
INSTALLS += target

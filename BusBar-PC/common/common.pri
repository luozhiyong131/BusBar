
include(excel/excel.pri)
include(charts/charts.pri)
include(logcom/logcom.pri)
include(sqlcom/sqlcom.pri)
include(rtucom/rtucom.pri)
include(config/config.pri)
include(snmp/snmp.pri)
include(tablecom/tablecom.pri)
include(websocket/websocket.pri)
include(serialport/serialport.pri)

INCLUDEPATH += $$PWD

HEADERS += \
    $$PWD/msgbox.h \   
    $$PWD/datapacket.h \
    $$PWD/common.h \
#    $$PWD/configbase.h
   
	
SOURCES += \
    $$PWD/msgbox.cpp \   
    $$PWD/common.cpp \
#    $$PWD/configbase.cpp
   

FORMS += \
    





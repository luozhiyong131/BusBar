
INCLUDEPATH += $$PWD

include(serialport/serialport.pri)
include(websockets/websockets.pri)
include(keyboard/keyboard.pri)
include(datetime/datetime.pri)
#include(excel/excel.pri)
include(beep/beep.pri)

HEADERS += \	
    $$PWD/sysconfigfile.h \
    $$PWD/common.h \
    $$PWD/box/msgbox.h \
#    $$PWD/chars/qcustomplot.h \
    $$PWD/rtucom/rtusentcom.h \
    $$PWD/datapacket.h \
    $$PWD/tablewid/comtablewid.h \
    $$PWD/tablewid/linetablewid.h \
    $$PWD/rtucom/rtuthread.h

   
	
SOURCES += \	
    $$PWD/sysconfigfile.cpp \
    $$PWD/common.cpp \
    $$PWD/box/msgbox.cpp \
#    $$PWD/chars/qcustomplot.cpp \
    $$PWD/rtucom/rtusentcom.cpp \
    $$PWD/tablewid/comtablewid.cpp \
    $$PWD/tablewid/linetablewid.cpp \
    $$PWD/rtucom/rtuthread.cpp
    
    

FORMS += \
    $$PWD/tablewid/comtablewid.ui



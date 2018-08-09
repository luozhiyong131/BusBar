
INCLUDEPATH += $$PWD

include(serialport/serialport.pri)
include(websockets/websockets.pri)
include(keyboard/keyboard.pri)
include(beep/beep.pri)

HEADERS += \	
    $$PWD/sysconfigfile.h \
    $$PWD/common.h \
    $$PWD/box/msgbox.h \
    $$PWD/chars/qcustomplot.h \
    $$PWD/datapacket.h

   
	
SOURCES += \	
    $$PWD/sysconfigfile.cpp \
    $$PWD/common.cpp \
    $$PWD/box/msgbox.cpp \
    $$PWD/chars/qcustomplot.cpp
    
    

FORMS += \



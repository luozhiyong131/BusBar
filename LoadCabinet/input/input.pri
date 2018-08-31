
INCLUDEPATH += $$PWD

HEADERS += \
    $$PWD/in_com/in_datapackets.h \
    $$PWD/in_rtu/in_rtusent.h \
    $$PWD/in_rtu/in_rturecv.h \
    $$PWD/in_rtu/in_rtupacket.h \
    $$PWD/in_rtu/in_rtutrans.h \
    $$PWD/in_tablewid/in_transtablewid.h \
    $$PWD/in_tablewid/in_envtablewid.h \
    $$PWD/in_tablewid/in_inputtablewid.h \
    $$PWD/in_tablewid/in_inputthresholdtablewid.h \
    $$PWD/in_mainwid.h
    
   
	
SOURCES += \
    $$PWD/in_com/in_datapackets.cpp \
    $$PWD/in_rtu/in_rtusent.cpp \
    $$PWD/in_rtu/in_rturecv.cpp \
    $$PWD/in_rtu/in_rtutrans.cpp \
    $$PWD/in_tablewid/in_transtablewid.cpp \
    $$PWD/in_tablewid/in_envtablewid.cpp \
    $$PWD/in_tablewid/in_inputtablewid.cpp \
    $$PWD/in_tablewid/in_inputthresholdtablewid.cpp \
    $$PWD/in_mainwid.cpp
    
    

FORMS += \
    $$PWD/in_mainwid.ui





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
    $$PWD/in_mainwid.h \
    $$PWD/in_rtu/in_rtuthread.h \
    $$PWD/in_set/in_setmainwid.h \
    $$PWD/in_set/in_setenvwid.h \
    $$PWD/in_set/in_setthresholdwid.h
    
   
	
SOURCES += \
    $$PWD/in_com/in_datapackets.cpp \
    $$PWD/in_rtu/in_rtusent.cpp \
    $$PWD/in_rtu/in_rturecv.cpp \
    $$PWD/in_rtu/in_rtutrans.cpp \
    $$PWD/in_tablewid/in_transtablewid.cpp \
    $$PWD/in_tablewid/in_envtablewid.cpp \
    $$PWD/in_tablewid/in_inputtablewid.cpp \
    $$PWD/in_tablewid/in_inputthresholdtablewid.cpp \
    $$PWD/in_mainwid.cpp \
    $$PWD/in_rtu/in_rtuthread.cpp \
    $$PWD/in_set/in_setmainwid.cpp \
    $$PWD/in_set/in_setenvwid.cpp \
    $$PWD/in_set/in_setthresholdwid.cpp
    
    

FORMS += \
    $$PWD/in_mainwid.ui \
    $$PWD/in_set/in_setmainwid.ui \
    $$PWD/in_set/in_setenvwid.ui \
    $$PWD/in_set/in_setthresholdwid.ui




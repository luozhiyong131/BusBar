
INCLUDEPATH += $$PWD

HEADERS += \
    $$PWD/bus_rtu/bus_rtucmdenum.h \
    $$PWD/bus_rtu/bus_rturecv.h \
    $$PWD/bus_rtu/bus_rtusent.h \
    $$PWD/bus_rtu/bus_rtutrans.h \
    $$PWD/bus_rtu/bus_rtuthread.h \
    $$PWD/bus_com/bus_datapackets.h \
    $$PWD/bus_com/bus_configfile.h \
    $$PWD/bus_thd/bus_thdchartwid.h \
    $$PWD/bus_thd/bus_thdmaindlg.h \
    $$PWD/bus_thd/bus_thdtablewid.h \
    $$PWD/bus_box/bus_boxlooptablewid.h \
    $$PWD/bus_box/bus_boxlinetablewid.h \
    $$PWD/bus_box/bus_boxdlg.h

	
SOURCES += \
    $$PWD/bus_rtu/bus_rturecv.cpp \
    $$PWD/bus_rtu/bus_rtusent.cpp \
    $$PWD/bus_rtu/bus_rtutrans.cpp \
    $$PWD/bus_rtu/bus_rtuthread.cpp \
    $$PWD/bus_com/bus_datapackets.cpp \
    $$PWD/bus_com/bus_configfile.cpp \
    $$PWD/bus_thd/bus_thdchartwid.cpp \
    $$PWD/bus_thd/bus_thdmaindlg.cpp \
    $$PWD/bus_thd/bus_thdtablewid.cpp \
    $$PWD/bus_box/bus_boxlooptablewid.cpp \
    $$PWD/bus_box/bus_boxlinetablewid.cpp \
    $$PWD/bus_box/bus_boxdlg.cpp

FORMS += \
    $$PWD/bus_thd/bus_thdmaindlg.ui \
    $$PWD/bus_box/bus_boxdlg.ui






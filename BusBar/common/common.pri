
INCLUDEPATH += $$PWD

HEADERS += \	
    $$PWD/common.h \
    $$PWD/msgbox.h \
#    $$PWD/ipsort.h \
#    $$PWD/icon/iconpath.h \
#    $$PWD/signaldispatch.h \
#    $$PWD/configtool.h
    common/sysconfigfile.h \
    common/datapacket.h
	
SOURCES += \	
    $$PWD/common.cpp \
    $$PWD/msgbox.cpp \
#    $$PWD/ipsort.cpp \
#    $$PWD/icon/iconpath.cpp \
#    $$PWD/signaldispatch.cpp \
#    $$PWD/configtool.cpp
    common/sysconfigfile.cpp \
    common/datapacket.cpp



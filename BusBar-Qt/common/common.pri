
INCLUDEPATH += $$PWD

HEADERS += \	
    $$PWD/common.h \
    $$PWD/msgbox.h \
    common/sysconfigfile.h \
    common/datapacket.h \
#    common/qcustomplot.h \
    $$PWD/myprogressbar.h \
    $$PWD/comtablewid.h
	
SOURCES += \	
    $$PWD/common.cpp \
    $$PWD/msgbox.cpp \
    common/sysconfigfile.cpp \
    common/datapacket.cpp \
#    common/qcustomplot.cpp \
    $$PWD/myprogressbar.cpp \
    $$PWD/comtablewid.cpp

FORMS += \
    $$PWD/comtablewid.ui





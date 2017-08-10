
INCLUDEPATH += $$PWD

HEADERS += \
    $$PWD/smtp/emailsetdlg.h \
    $$PWD/smtp/email.h \
    $$PWD/smtp/smtp.h \
    $$PWD/smtp/smtpssl.h \
    $$PWD/smtp/emailwid.h \
    $$PWD/smtp/emailthread.h \
    $$PWD/excel/basicExcel/BasicExcel.hpp \
    $$PWD/excel/excelexportlogthread.h \
    $$PWD/excel/excelexportwid.h \
    $$PWD/excel/txtexportlogthread.h \
    $$PWD/network/android_tcp_server.h \
    $$PWD/network/devDataSent.h \
    $$PWD/network/devDataType.h \
    $$PWD/network/netDataPacket.h \
    $$PWD/network/netDataSegment.h \
    $$PWD/network/tcpserver.h \
    $$PWD/network/udpdebug.h \
    $$PWD/network/udpHbPacket.h \
    $$PWD/network/udpsent.h \
    $$PWD/network/udpservice.h \
    $$PWD/datetime/timesettingdlg.h
    
   
	
SOURCES += \
    $$PWD/smtp/emailsetdlg.cpp \
    $$PWD/smtp/email.cpp \
    $$PWD/smtp/smtp.cpp \
    $$PWD/smtp/smtpssl.cpp \
    $$PWD/smtp/emailwid.cpp \
    $$PWD/smtp/emailthread.cpp \
    $$PWD/excel/basicExcel/BasicExcel.cpp \
    $$PWD/excel/execl_demo.cpp \
    $$PWD/excel/excelexportlogthread.cpp \
    $$PWD/excel/excelexportwid.cpp \
    $$PWD/excel/txtexportlogthread.cpp \
    $$PWD/network/android_tcp_server.c \
    $$PWD/network/devDataSent.c \
    $$PWD/network/netDataPacket.c \
    $$PWD/network/netDataSegment.c \
    $$PWD/network/tcpserver.c \
    $$PWD/network/udpHbPacket.c \
    $$PWD/network/udpsent.c \
    $$PWD/network/udpservice.c \
    $$PWD/datetime/timesettingdlg.cpp
    

FORMS += \
    $$PWD/smtp/emailsetdlg.ui \
    $$PWD/smtp/emailwid.ui \
    $$PWD/excel/excelexportwid.ui \
    $$PWD/datetime/timesettingdlg.ui



INCLUDEPATH +=  $$PWD/udp/recv \
                $$PWD/udp/sent \
                $$PWD/tcp/client \
                $$PWD/datadone \
                $$PWD/analyze \

INCLUDEPATH += $$PWD

HEADERS += \
    $$PWD/udp/sent/udpheartbeat.h \
    $$PWD/udp/sent/udpsentsocket.h \
    $$PWD/udp/recv/udprecvsocket.h \
    $$PWD/tcp/client/tcpclient.h \
    $$PWD/tcp/client/tcpsent.h \
    $$PWD/tcp/server/tcpserver.h \
    $$PWD/analyze/netdataanalyze.h \
    $$PWD/datadone/netanalyzedata.h \
    $$PWD/datadone/netdataformat.h \
    $$PWD/datadone/netpackdata.h \
    $$PWD/network.h \
    $$PWD/save/pduhashcom.h \
    $$PWD/save/pduhashdevdatasave.h \
    $$PWD/save/pduhashdatasave.h
    
	
SOURCES += \
    $$PWD/udp/sent/udpheartbeat.cpp \
    $$PWD/udp/sent/udpsentsocket.cpp \
    $$PWD/udp/recv/udprecvsocket.cpp \
    $$PWD/tcp/client/tcpclient.cpp \
    $$PWD/tcp/client/tcpsent.cpp \
    $$PWD/tcp/server/tcpserver.cpp \
    $$PWD/analyze/netdataanalyze.cpp \
    $$PWD/datadone/netanalyzedata.cpp \
    $$PWD/datadone/netpackdata.cpp \
    $$PWD/network.cpp \
    $$PWD/save/pduhashcom.cpp \
    $$PWD/save/pduhashdevdatasave.cpp \
    $$PWD/save/pduhashdatasave.cpp
    


	


INCLUDEPATH += $$PWD

HEADERS += \
    $$PWD/smtp/emailsetdlg.h \
    $$PWD/smtp/email.h \
    $$PWD/smtp/smtp.h \
    $$PWD/smtp/smtpssl.h \
    $$PWD/smtp/emailwid.h \
    $$PWD/smtp/emailthread.h
    
   
	
SOURCES += \
    $$PWD/smtp/emailsetdlg.cpp \
    $$PWD/smtp/email.cpp \
    $$PWD/smtp/smtp.cpp \
    $$PWD/smtp/smtpssl.cpp \
    $$PWD/smtp/emailwid.cpp \
    $$PWD/smtp/emailthread.cpp
    

FORMS += \
    $$PWD/smtp/emailsetdlg.ui \
    $$PWD/smtp/emailwid.ui



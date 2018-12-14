
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
    $$PWD/bus_box/bus_boxdlg.h \
    $$PWD/bus_branch/bus_branchtablewid.h \
    $$PWD/bus_branch/bus_branchwid.h \
    $$PWD/bus_line/bus_linetablewid.h \
    $$PWD/bus_line/bus_linewid.h \
    $$PWD/bus_sql/bus_dbalarm.h \
    $$PWD/bus_sql/bus_dbbranchele.h \
    $$PWD/bus_sql/bus_dbname.h \
    $$PWD/bus_sql/bus_dblineele.h \
    $$PWD/bus_logs/bus_logalarmwid.h \
    $$PWD/bus_logs/bus_loglineelewid.h \
    $$PWD/bus_logs/bus_logbranchelewid.h \
    $$PWD/bus_home/bus_homeboxwid.h \
    $$PWD/bus_home/bus_homewid.h \
    $$PWD/bus_com/bus_setshm.h \
    $$PWD/bus_setting/setthreshold/setrtucmd.h \
    $$PWD/bus_setting/setthreshold/setthread.h \
    $$PWD/bus_setting/setthreshold/setthresholddlg.h \
    $$PWD/bus_setting/setline/setlineitem.h \
    $$PWD/bus_setting/setline/myprogressbar.h \
    $$PWD/bus_setting/setline/setlinewid.h \
    $$PWD/bus_setting/settem/setlinetem.h \
    $$PWD/bus_setting/setloop/setloopwid.h \
    $$PWD/bus_setting/settem/settemmain.h \
    $$PWD/bus_setting/settem/setlooptemwid.h \
    $$PWD/bus_setting/setnames/setnamedlg.h \
    $$PWD/bus_setting/setnames/setnameswid.h \
    $$PWD/bus_setting/setsystem/checkpassworddlg.h \
    $$PWD/bus_setting/setsystem/mynumberkeyboardwid.h \
    $$PWD/bus_setting/setsystem/ipsettingdlg.h \
    $$PWD/bus_setting/setsystem/passordsettingdlg.h \
    $$PWD/bus_setting/setsystem/systemsettingdlg.h \
    $$PWD/bus_logs/bus_logswid.h \
    $$PWD/bus_dp/bus_dpalarmslave.h \
    $$PWD/bus_dp/bus_dpalarmthread.h \
    $$PWD/bus_dp/bus_dpeleslavethread.h \
    $$PWD/bus_dp/bus_dptgthread.h \
    $$PWD/bus_dp/bus_dpthread.h

	
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
    $$PWD/bus_box/bus_boxdlg.cpp \
    $$PWD/bus_branch/bus_branchtablewid.cpp \
    $$PWD/bus_branch/bus_branchwid.cpp \
    $$PWD/bus_line/bus_linetablewid.cpp \
    $$PWD/bus_line/bus_linewid.cpp \
    $$PWD/bus_sql/bus_dbalarm.cpp \
    $$PWD/bus_sql/bus_dbbranchele.cpp \
    $$PWD/bus_sql/bus_dbname.cpp \
    $$PWD/bus_sql/bus_dblineele.cpp \
    $$PWD/bus_logs/bus_logalarmwid.cpp \
    $$PWD/bus_logs/bus_loglineelewid.cpp \
    $$PWD/bus_logs/bus_logbranchelewid.cpp \
    $$PWD/bus_home/bus_homeboxwid.cpp \
    $$PWD/bus_home/bus_homewid.cpp \
    $$PWD/bus_com/bus_setshm.cpp \
    $$PWD/bus_setting/setthreshold/setrtucmd.cpp \
    $$PWD/bus_setting/setthreshold/setthread.cpp \
    $$PWD/bus_setting/setthreshold/setthresholddlg.cpp \
    $$PWD/bus_setting/setline/setlineitem.cpp \
    $$PWD/bus_setting/setline/myprogressbar.cpp \
    $$PWD/bus_setting/setline/setlinewid.cpp \
    $$PWD/bus_setting/settem/setlinetem.cpp \
    $$PWD/bus_setting/setloop/setloopwid.cpp \
    $$PWD/bus_setting/settem/settemmain.cpp \
    $$PWD/bus_setting/settem/setlooptemwid.cpp \
    $$PWD/bus_setting/setnames/setnamedlg.cpp \
    $$PWD/bus_setting/setnames/setnameswid.cpp \
    $$PWD/bus_setting/setsystem/checkpassworddlg.cpp \
    $$PWD/bus_setting/setsystem/mynumberkeyboardwid.cpp \
    $$PWD/bus_setting/setsystem/ipsettingdlg.cpp \
    $$PWD/bus_setting/setsystem/passordsettingdlg.cpp \
    $$PWD/bus_setting/setsystem/systemsettingdlg.cpp \
    $$PWD/bus_logs/bus_logswid.cpp \
    $$PWD/bus_dp/bus_dpalarmslave.cpp \
    $$PWD/bus_dp/bus_dpalarmthread.cpp \
    $$PWD/bus_dp/bus_dpeleslavethread.cpp \
    $$PWD/bus_dp/bus_dptgthread.cpp \
    $$PWD/bus_dp/bus_dpthread.cpp

FORMS += \
    $$PWD/bus_thd/bus_thdmaindlg.ui \
    $$PWD/bus_box/bus_boxdlg.ui \
    $$PWD/bus_branch/bus_branchwid.ui \
    $$PWD/bus_line/bus_linewid.ui \
    $$PWD/bus_home/bus_homeboxwid.ui \
    $$PWD/bus_home/bus_homewid.ui \
    $$PWD/bus_setting/setthreshold/setthresholddlg.ui \
    $$PWD/bus_setting/setline/setlineitem.ui \
    $$PWD/bus_setting/setline/setlinewid.ui \
    $$PWD/bus_setting/settem/setlinetem.ui \
    $$PWD/bus_setting/settem/settemmain.ui \
    $$PWD/bus_setting/setnames/setnamedlg.ui \
    $$PWD/bus_setting/setnames/setnameswid.ui \
    $$PWD/bus_setting/setsystem/checkpassworddlg.ui \
    $$PWD/bus_setting/setsystem/mynumberkeyboardwid.ui \
    $$PWD/bus_setting/setsystem/ipsettingdlg.ui \
    $$PWD/bus_setting/setsystem/passordsettingdlg.ui \
    $$PWD/bus_setting/setsystem/systemsettingdlg.ui \
    $$PWD/bus_logs/bus_logswid.ui






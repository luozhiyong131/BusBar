#include "interfacechangesig.h"
#include "beepthread.h"

InterfaceChangeSig::InterfaceChangeSig(QObject *parent) : QObject(parent)
{
}

InterfaceChangeSig::~InterfaceChangeSig()
{
}

InterfaceChangeSig *InterfaceChangeSig::get(QObject *parent)
{
    static InterfaceChangeSig *sington = NULL;
    if(!sington) {
        sington = new InterfaceChangeSig(parent);
    }
    return sington;
}

void InterfaceChangeSig::changeType(int type)
{
    emit typeSig(type);
    BeepThread::bulid()->beep();
}

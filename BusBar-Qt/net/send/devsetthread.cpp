#include "devsetthread.h"



DevSetThread::DevSetThread(QObject *parent) : QThread(parent)
{
    isRun = false;

}

DevSetThread *DevSetThread::bulid()
{
    static DevSetThread* sington = NULL;
        if(sington == NULL)
            sington = new DevSetThread();
        return sington;
}

void DevSetThread::run()
{
    while (1) {
        if(gDevList.size()){ //释放缓存
            isRun = true;


        }else{
            isRun = false;
            sleep(1000);
        }

    }
}

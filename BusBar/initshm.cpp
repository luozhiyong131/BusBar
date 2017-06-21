#include "initshm.h"

InitShm::InitShm(QObject *parent) : QObject(parent)
{
    shm = get_share_mem(); // 获取共享内存
    initBoxNum();
}

/**
 * @brief 初始化插接箱数量
 */
void InitShm::initBoxNum()
{
    for(int i=0; i<BUS_NUM; ++i) {
        shm->data[i].boxNum = 18; // 18个插接箱
    }
}

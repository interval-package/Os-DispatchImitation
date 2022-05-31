//
// Created by Zza on 2022/5/8.
//

#ifndef OS_DISPATCHIMITATION_DISPATCHACTION_H
#define OS_DISPATCHIMITATION_DISPATCHACTION_H

#include "../Process/Process.h"

class DispatchAction {
public:
    Process main;

//    这里的主要内容还是就是进行一个Process的初始化
    DispatchAction(Memory *mem, Disk *disk, int workspace_size);

//    for the usage of multi thread
    void operator()();

    void input_ad_series();

private:
//    存放我们的过程序列
    ACTIONS acts;

};

#endif //OS_DISPATCHIMITATION_DISPATCHACTION_H

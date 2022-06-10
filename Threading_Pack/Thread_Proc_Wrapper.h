//
// Created by Zza on 2022/5/8.
//

#ifndef OS_DISPATCHIMITATION_THREAD_PROC_WRAPPER_H
#define OS_DISPATCHIMITATION_THREAD_PROC_WRAPPER_H

#include "../Process/Process.h"

class Thread_Proc_Wrapper {
//    这个是针对对线程特定使用的，封装了互斥访问的内容
public:
    Process main;

//    这里的主要内容还是就是进行一个Process的初始化
    Thread_Proc_Wrapper(Memory *mem, Disk *disk, int workspace_size);

//    for the usage of multi thread
    void operator()();

    void input_ad_series();

    void input_ad_series_detail();

//    外包装的外部调用函数，没有实现线程安全
    static void outer_run(Thread_Proc_Wrapper proc);

//    外包装的外部调度函数，实现线程安全
//    进行优化升级
    static void outer_main(Thread_Proc_Wrapper proc);

    void inner_main();

private:
//    存放我们的过程序列

    struct _acts{
        int ad;
        bool is_write;
    };

    typedef std::vector<_acts> _action;
    ACTIONS acts;
    _action _detail_act;

};


#endif //OS_DISPATCHIMITATION_THREAD_PROC_WRAPPER_H

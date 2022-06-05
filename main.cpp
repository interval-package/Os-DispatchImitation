#include <iostream>
#include "./Kernel/PageLinkedList/PageLinkedList.h"
#include "Process/Process.h"

#include "Threading_Pack/Thread_Proc_Wrapper.h"

#include <thread>

using namespace std;

int work_space = 3;

void disp_init_interface();

void main_without_thread(Memory &mem,Disk &disk);

void main_with_thread(Memory &mem,Disk &disk);

void input_set_dispatch_type(Process& proc);

int main() {
    Memory mem;
    Disk disk;

//    将当前配置环境打印

    disp_init_interface();

//    main_without_thread(mem,disk);

    main_with_thread(mem,disk);

    return 0;
}

void main_without_thread(Memory &mem,Disk &disk){
    Process proc(&mem,&disk,work_space);

    ACTIONS acts;
//    设置访问序列

    int act;

    cout<<"please input a series of tar ad(end with -1): ";

    while (cin>>act){
        if (act > 0){
            acts.push_back(act);
        } else{
            break;
        }
    }

//    按访问序列的方式访问
    proc.run(acts);

//    按照步进的方式访问
    proc.run();
}

void main_with_thread(Memory &mem,Disk &disk){
    Thread_Proc_Wrapper proc1(&mem, &disk, work_space);
    Thread_Proc_Wrapper proc2(&mem, &disk, work_space);
    Thread_Proc_Wrapper proc3(&mem, &disk, work_space);

    input_set_dispatch_type(proc1.main);
    proc1.input_ad_series_detail();

    input_set_dispatch_type(proc2.main);
    proc2.input_ad_series_detail();

    input_set_dispatch_type(proc3.main);
    proc3.input_ad_series_detail();

    cout<<endl;

//    c++，要是使用引用类型的传参会有问题的，所以不行
    thread th1(Thread_Proc_Wrapper::outer_main, proc1);
    thread th2(Thread_Proc_Wrapper::outer_main, proc2);
    thread th3(Thread_Proc_Wrapper::outer_main, proc3);

    th1.join();
    th2.join();
    th3.join();

}

void disp_init_interface(){
/*
 * 显示开始时进行简介函数
 * 默认认为我们使用常变量进行环境的配置
 * 所以我们这里可以直接进行初始化后内容的打印
 * */

    cout<<"==============================================="<<endl;
    cout<<"memory size:\t"<<Memory::INIT_MEMORY_SIZE<<" frames"<<endl;
    cout<<"Disk size:\t"<<Disk::INIT_DISK_SIZE<<" frames"<<endl;
    cout<<"page length:\t"<<PageFrame::PAGE_LENGTH<<" bytes"<<endl;
    cout<<"page nums:\t"<<PageList::LIST_LENGTH<<endl;
    cout<<"work set size:\t"<<work_space<<endl;
    cout<<"please enter address like {block id}*{page length}"<<endl;
    cout<<"==============================================="<<endl;

}

void input_set_dispatch_type(Process& proc){
    cout<<"***************************\n"
          "input your target disp type\n"
          "case 'i': _dsp_FIFO();\n"
          "case 'r': _dsp_LRU();\n"
          "case 'f': _dsp_LFU();\n"
          "case 'c': _dsp_clock();\n"
          "***************************\n"
          "yours:"<<endl;
    char temp;
    cin>>temp;
    proc.set_dispatch_type(temp);
}
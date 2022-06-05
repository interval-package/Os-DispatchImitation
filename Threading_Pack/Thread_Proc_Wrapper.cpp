//
// Created by Zza on 2022/5/8.
//

#include "Thread_Proc_Wrapper.h"
#include <mutex>
#include <windows.h>

std::mutex disp_mutex;
std::mutex input_mutex;

static const int sleep_time = 1000;

void Thread_Proc_Wrapper::input_ad_series() {
//    设置访问序列
    int act;

    std::cin.clear();
    std::cout<<std::endl<<"please input a series of tar ad(end with -1): ";
    while (std::cin>>act){
        if (act > 0){
            acts.push_back(act);
        } else{
            break;
        }
    }
    std::cout.flush();
}

void Thread_Proc_Wrapper::input_ad_series_detail() {
    //    设置访问序列
    int tar;
    _acts act{};

    std::cin.clear();
    std::cout<<std::endl<<"please input a series of tar ad\n"
                          "if write <0\n"
                          "(end with 0): ";
    while (std::cin>>tar){
        if(tar==0)break;
        act.ad = abs(tar);
        act.is_write = tar < 0;
        this->_detail_act.push_back(act);
    }
    std::cout.flush();
}

void Thread_Proc_Wrapper::operator()() {
    this->main.run(acts);
}

Thread_Proc_Wrapper::Thread_Proc_Wrapper(Memory *mem, Disk *disk, int workspace_size)
:main(mem, disk, workspace_size) {
    std::cout<<"proc "<<this->main.id<<" wrapped with multi thread"<<std::endl;
}

void Thread_Proc_Wrapper::outer_run(Thread_Proc_Wrapper proc){
    using namespace std;
    cout<<"Dispatch threading!"<<endl;
    proc.main.run(proc.acts);
}

void Thread_Proc_Wrapper::outer_main(Thread_Proc_Wrapper proc) {
    using namespace std;
    cout<<"Dispatch safe threading!"<<endl;
    for(auto iter: proc._detail_act){
        disp_mutex.lock();
        cout<<"================================="<<endl;
        cout<<"proc id : "<<proc.main.id<<endl;
        proc.main.single_step(iter.ad,iter.is_write);
        cout<<"================================="<<endl;
        disp_mutex.unlock();
        Sleep(sleep_time);
    }
}



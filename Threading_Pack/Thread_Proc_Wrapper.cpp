//
// Created by Zza on 2022/5/8.
//

#include "Thread_Proc_Wrapper.h"
#include <mutex>

std::mutex disp_mutex;
std::mutex input_mutex;

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

void Thread_Proc_Wrapper::operator()() {
    this->main.run(acts);
}

Thread_Proc_Wrapper::Thread_Proc_Wrapper(Memory *mem, Disk *disk, int workspace_size)
:main(mem, disk, workspace_size) {
}

void Thread_Proc_Wrapper::outer_run(Thread_Proc_Wrapper proc){
    using namespace std;
    cout<<"Dispatch threading!"<<endl;
    proc.main.run(proc.acts);
}

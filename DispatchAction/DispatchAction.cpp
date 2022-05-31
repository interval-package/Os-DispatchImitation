//
// Created by Zza on 2022/5/8.
//

#include "DispatchAction.h"

void DispatchAction::input_ad_series() {
//    设置访问序列
    int act;

    std::cout<<"please input a series of tar ad(end with -1): ";
    while (std::cin>>act){
        if (act > 0){
            acts.push_back(act);
        } else{
            break;
        }
    }
}

void DispatchAction::operator()() {
    this->main.run(acts);
}

DispatchAction::DispatchAction(Memory *mem, Disk *disk, int workspace_size)
:main(mem, disk, workspace_size) {
}

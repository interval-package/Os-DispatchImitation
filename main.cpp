#include <iostream>
#include <vector>
#include "./Kernel/PageLinkedList/PageLinkedList.h"
#include "Process/Process.h"

using namespace std;

int main() {
    ACTIONS acts;
//    设置访问序列

    int act;

    while (cin>>act){
        if (act > 0){
            acts.push_back(act);
        } else{
            break;
        }
    }

    Memory mem;
    Disk disk;
    Process proc(&mem,&disk,16);

//    还需要初始化页表

//    设置访问序列
    proc.run(acts);

    return 0;
}

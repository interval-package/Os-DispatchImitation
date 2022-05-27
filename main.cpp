#include <iostream>
#include <vector>
#include "./Kernel/PageLinkedList/PageLinkedList.h"
#include "Process/Process.h"

using namespace std;

int main() {
    Memory mem;
    Disk disk;
    Process proc(&mem,&disk,16);

//    将当前配置环境打印



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

//    设置访问序列
    proc.run(acts);

    return 0;
}

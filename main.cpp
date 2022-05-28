#include <iostream>
#include <vector>
#include "./Kernel/PageLinkedList/PageLinkedList.h"
#include "Process/Process.h"

using namespace std;

int main() {
    int work_space = 3;

    Memory mem;
    Disk disk;
    Process proc(&mem,&disk,work_space);

//    将当前配置环境打印
    cout<<"==============================================="<<endl;
    cout<<"memory size:\t"<<Memory::INIT_MEMORY_SIZE<<" frames"<<endl;
    cout<<"Disk size:\t"<<Disk::INIT_DISK_SIZE<<" frames"<<endl;
    cout<<"page length:\t"<<PageFrame::PAGE_LENGTH<<" bytes"<<endl;
    cout<<"page nums:\t"<<PageList::LIST_LENGTH<<endl;
    cout<<"work set size:\t"<<work_space<<endl;
    cout<<"please enter address like {block id}*{page length}"<<endl;
    cout<<"==============================================="<<endl;

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

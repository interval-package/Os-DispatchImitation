#include <iostream>
#include <vector>
#include "./Kernel/PageLinkedList/PageLinkedList.h"
#include "Process/Process.h"

using namespace std;

int main() {
    ACTIONS acts;
//    设置访问序列

    Memory mem;
    Disk disk;
    Process proc(&mem,&disk,16);

//    设置访问序列
    proc.run(acts);

    return 0;
}

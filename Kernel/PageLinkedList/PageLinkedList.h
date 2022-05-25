//
// Created by Zza on 2022/5/8.
//

#ifndef OS_DISPATCHIMITATION_PAGELINKEDLIST_H
#define OS_DISPATCHIMITATION_PAGELINKEDLIST_H

#include "../PageItem/PageItem.h"
#include "../../EnvImitator/Resource_Memory/Memory.h"



// 将会在该函数内部进行调度，算法的实现
// 这里还要实现，内存的申请和分配

class PageLinkedList {
private:
//    我们将目前所有的page项，使用链表进行连接
    typedef struct Node{
        PageItem* data;
        Node* next;
    } Node, *pNode;

    int WorkSetLen;

    void add_work_node(PageItem* tar);

    Memory *mem;

public:
    PageLinkedList(int len, Memory* tar);

    Node* head_WorkSet;
    Node* head_StaySet;

    ~PageLinkedList();

};


#endif //OS_DISPATCHIMITATION_PAGELINKEDLIST_H

//
// Created by Zza on 2022/5/8.
//

#ifndef OS_DISPATCHIMITATION_PAGELINKEDLIST_H
#define OS_DISPATCHIMITATION_PAGELINKEDLIST_H

#include "../PageItem/PageItem.h"
#include "../../EnvImitator/Resource_Memory/Memory.h"
#include "../../Exceptions/Exception_BoundExceed.h"

// 将会在该函数内部进行调度，算法的实现
// 这里还要实现，内存的申请和分配

class PageLinkedList {
private:
//    我们将目前所有的page项，使用链表进行连接
    typedef struct Node{
        PageItem* data;
        Node* next;
        Node* prior;
    } Node, *pNode;
    int WorkSetLen;
    void add_work_node(PageItem* tar);
    PageItem* de_work_node();
    Memory *mem;

//    PageItem* (*_detail_dispatch)(PageItem* tar);

//    作为调度算法，要实现调度结果的插入与返回
    PageItem* _dsp_FIFO(PageItem* tar);

    PageItem* _dsp_LRU(PageItem* tar);

public:
    PageLinkedList(int len, Memory* tar);

//    做了一个双向链表作为模拟
    Node* head_WorkSet;
    Node* head_StaySet;

    PageItem* dispatching(PageItem* tar);

    void set_dispatch_type(char type);

    ~PageLinkedList();

    void display_cur();

};


#endif //OS_DISPATCHIMITATION_PAGELINKEDLIST_H

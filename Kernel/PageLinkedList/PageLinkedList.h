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

//    使用这个长度来判断，链表是否为满
    const int _len;
    int WorkSetLen;

//    模拟队列操作，入队出队
    void add_work_node(PageItem* tar);
    PageItem* de_work_node();

//    内存对象，目前还没有明确用途
    Memory *mem;

//    作为调度算法，要实现的是找到目标的位置
    pNode _dsp_FIFO(PageItem* tar) const;

//    PageItem* _dsp_LRU(PageItem* tar);

    void cut_node(pNode pos);

public:
    PageLinkedList(int len, Memory* tar);

//    做了一个双向链表作为模拟
    Node* head_WorkSet;
    Node* head_StaySet;

    PageItem* inner_dispatching(PageItem* tar);

//    void set_dispatch_type(char type);

    ~PageLinkedList();

    void display_cur() const;

};


#endif //OS_DISPATCHIMITATION_PAGELINKEDLIST_H

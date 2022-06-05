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
    void cut_node(pNode pos);
    PageItem* de_work_node();

//    内存对象，目前还没有明确用途
    Memory *mem;

public:
    PageLinkedList(int len, Memory* tar);

//    case 'i': _dsp_FIFO();
//    case 'r': _dsp_LRU();
//    case 'f': _dsp_LFU();
//    case 'c': _dsp_clock();
    char _dsp_type = 'f';

//    做了一个双向链表作为模拟
    Node* head_WorkSet;
    Node* head_StaySet;

//    inner dispatching with detail actions
    PageItem* inner_dispatching(PageItem* tar);

//    void set_dispatch_type(char type);

    ~PageLinkedList();

    void display_cur() const;

private:

//    作为调度算法，要实现的是找到目标的位置
//    在核心调度算法中，我们不做，插入与删除的操作
//    我们所做的,只是找出对应的节点指针,后面的操作交给外部包装函数
//    我们保证,在这里我们的链表一定是满的
    pNode _dsp_FIFO() const;

    pNode _dsp_LRU() const;

    pNode _dsp_LFU() const;

    pNode _dsp_clock() const;

    pNode _dsp_advClock() const;

//    pNode _dsp_WorkSet() const;
//
//    pNode _dsp_wsClock() const;

};

#endif //OS_DISPATCHIMITATION_PAGELINKEDLIST_H

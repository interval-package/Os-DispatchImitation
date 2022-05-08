//
// Created by Zza on 2022/5/8.
//

#ifndef OS_DISPATCHIMITATION_PAGELINKEDLIST_H
#define OS_DISPATCHIMITATION_PAGELINKEDLIST_H

#include "../PageItem/PageItem.h"

class PageLinkedList {
private:
//    我们将目前所有的page项，使用链表进行连接
    typedef struct Node{
        PageItem* data;
        Node* next;
    } Node, *pNode;
    Node head;
public:
    PageLinkedList();

};


#endif //OS_DISPATCHIMITATION_PAGELINKEDLIST_H

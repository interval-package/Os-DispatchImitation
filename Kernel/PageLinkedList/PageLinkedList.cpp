//
// Created by Zza on 2022/5/8.
//

#include "PageLinkedList.h"

PageLinkedList::PageLinkedList(int len, Memory *tar):
WorkSetLen(len), mem(tar)
{
    this->head_WorkSet = nullptr;
    this->head_StaySet = nullptr;
}

PageLinkedList::~PageLinkedList() {
    pNode temp = this->head_WorkSet, _temp;
//    clear the space
    while (temp){
        _temp = temp->next;
        delete temp;
        temp = _temp;
    }
    temp = this->head_StaySet;
    while (temp){
        _temp = temp->next;
        delete temp;
        temp = _temp;
    }
}

void PageLinkedList::add_work_node(PageItem *tar) {
    auto temp = new Node;
    if(this->head_WorkSet){
        temp->next = this->head_WorkSet->next;
        this->head_WorkSet->next = temp;
    } else{
        this->head_WorkSet = temp;
        temp->next = this->head_WorkSet;
    }
}

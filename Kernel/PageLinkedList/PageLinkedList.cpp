//
// Created by Zza on 2022/5/8.
//

#include "PageLinkedList.h"

PageLinkedList::PageLinkedList(int len, Memory *tar):
WorkSetLen(len), mem(tar)
{
    this->head_WorkSet = nullptr;
    this->head_StaySet = nullptr;
//    this->_detail_dispatch = this->_dsp_FIFO;
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
    temp->data = tar;
    if(this->head_WorkSet){
//        双链表，头插，总共要修改关系指针*4，头指针*1
        temp->next = this->head_WorkSet;
        temp->prior = this->head_WorkSet->prior;
        temp->prior->next = temp;
        this->head_WorkSet->prior = temp;

        this->head_WorkSet = temp;
    } else{
        this->head_WorkSet = temp;
        temp->next = this->head_WorkSet;
        temp->prior = this->head_WorkSet;
    }
}

PageItem *PageLinkedList::_dsp_FIFO(PageItem *tar) {
    return nullptr;
}

PageItem *PageLinkedList::de_work_node() {
    if(!this->head_WorkSet){
        throw Exception_BoundExceed();
    }
    pNode temp_node = this->head_WorkSet->prior;
    PageItem *res = temp_node->data;
    if(temp_node->next == temp_node){
        delete temp_node;
        this->head_WorkSet = nullptr;
    } else{
        this->head_WorkSet->prior = temp_node->prior;
        this->head_WorkSet->prior->next = this->head_WorkSet;
        delete temp_node;
    }
    return res;
}

PageItem *PageLinkedList::_dsp_LRU(PageItem *tar) {
    return nullptr;
}

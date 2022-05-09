//
// Created by Zza on 2022/5/8.
//

#include "PageLinkedList.h"

PageLinkedList::PageLinkedList(){
    this->head_WorkSet.data = NULL;
    this->head_WorkSet.next = &this->head_WorkSet;
};

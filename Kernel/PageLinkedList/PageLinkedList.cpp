//
// Created by Zza on 2022/5/8.
//

#include "PageLinkedList.h"

PageLinkedList::PageLinkedList(){
    this->head.data = NULL;
    this->head.next = &this->head;
};

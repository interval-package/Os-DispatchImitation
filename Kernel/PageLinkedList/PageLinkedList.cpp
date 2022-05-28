//
// Created by Zza on 2022/5/8.
//

#include "PageLinkedList.h"

PageLinkedList::PageLinkedList(int len, Memory *tar):
WorkSetLen(len), mem(tar), _len(len)
{
    this->head_WorkSet = nullptr;
    this->head_StaySet = nullptr;
//    this->_detail_dispatch = this->_dsp_FIFO;
}

PageLinkedList::~PageLinkedList() {
    pNode temp = this->head_WorkSet, _temp = nullptr;
//    clear the space
    while (_temp != this->head_WorkSet){
        _temp = temp->next;
        delete temp;
        temp = _temp;
    }
    temp = this->head_StaySet;
    _temp = nullptr;
    while (_temp != this->head_StaySet){
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
    this->WorkSetLen--;
}

PageItem *PageLinkedList::de_work_node() {
//    这个就完全是栈的操作了,会考虑到空的情况

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
    this->WorkSetLen++;
    return res;
}

void PageLinkedList::cut_node(PageLinkedList::pNode pos) {
//    this function only clear the node but not to return the data
//    要注意的是,这个函数只在清理的时候,进行使用,也就是说会保证链表至少有两个以上的元素

    pos->next->prior = pos->prior;
    pos->prior->next = pos->next;
    this->WorkSetLen++;

    if(pos == this->head_WorkSet){
        this->head_WorkSet = pos->next;
    }

    delete pos;
}

PageItem *PageLinkedList::inner_dispatching(PageItem *tar) {
//    在调度函数中，我们所做的，只是
    if(this->WorkSetLen){
        std::cout<<"adding node success"<<std::endl;
        this->add_work_node(tar);
        return nullptr;
    }
    pNode old;
    switch (_dsp_type) {
        case 'i':{
            old = _dsp_FIFO();
            break;
        }
        case 'r':{
            old = _dsp_LRU();
            break;
        }
        case 'f':{
            old = _dsp_LFU();
            break;
        }
        case 'c':{
            old = _dsp_clock();
            break;
        }
        default: old = _dsp_FIFO();
    }
    PageItem* res = old->data;
    this->cut_node(old);
//    新来的节点都是头插
    this->add_work_node(tar);
    return res;
}

void PageLinkedList::display_cur() const {
    using namespace std;

    pNode temp = this->head_WorkSet;
    pNode iter = temp;

    cout<<"**********************"<<endl;
    cout<<"displaying link detail"<<endl;
    cout<<"remaining area:"<<this->WorkSetLen<<endl;

    if(!temp){
        cout<<"the list is empty"<<endl;
        return;
    }

    cout<<"the detail:"<<endl;

    do {
        cout<<"->"<<endl;
        iter->data->disp_self();
        iter = iter->next;
    } while (iter != temp);

    cout<<"**********************"<<endl;
}

PageLinkedList::pNode PageLinkedList::_dsp_FIFO() const {
//    所以就很直接,返回尾巴就好了
    std::cout<<"processing FIFO method."<<std::endl;
    return this->head_WorkSet->prior;
}

PageLinkedList::pNode PageLinkedList::_dsp_LRU() const {
    std::cout<<"processing LRU method."<<std::endl;
    pNode temp, judge, res;
    res = judge = this->head_WorkSet;
    temp = judge->next;

    int pivot = judge->data->recentAccess;

    while (temp!=judge){
        if(temp->data->recentAccess < pivot){
            res = temp;
            pivot = temp->data->recentAccess;
        }
        temp=temp->next;
    }
    return res;
}

PageLinkedList::pNode PageLinkedList::_dsp_LFU() const {
    std::cout<<"processing LFU method."<<std::endl;
    pNode temp, judge, res;
    res = judge = this->head_WorkSet;
    temp = judge->next;

    int pivot = judge->data->accessTimes;

    while (temp!=judge){
        if(temp->data->accessTimes < pivot){
            res = temp;
            pivot = temp->data->accessTimes;
        }
        temp=temp->next;
    }
    return res;
}

PageLinkedList::pNode PageLinkedList::_dsp_clock() const {
    std::cout<<"processing clock method."<<std::endl;
    pNode temp, res;
    temp = this->head_WorkSet;

    while (temp->data->accessTimes){
        temp->data->accessTimes = 0;
        temp = temp->prior;
    }

    res = temp;
    return res;
}

PageLinkedList::pNode PageLinkedList::_dsp_advClock() const {
//    改进时钟算法，做最多四次遍历
    std::cout<<"processing LFU method."<<std::endl;
    pNode temp, judge, res;
    judge = this->head_WorkSet;
    temp = judge;

    for(int i=0; i<2; i++){
        do {
            if(!temp->data->isWritten && !temp->data->accessTimes){
                return temp;
            }
            temp=temp->next;
        } while (temp!=judge);

        do {
            if(temp->data->isWritten && !temp->data->accessTimes){
                return temp;
            }
            temp->data->accessTimes = 0;
            temp=temp->next;
        } while (temp!=judge);

    }

    return temp;
}



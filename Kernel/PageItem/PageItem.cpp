//
// Created by Zza on 2022/5/8.
//

#include "PageItem.h"
#include <iostream>

int Page_item_time = 0;

void PageItem::disp_self() const {
    using namespace std;
    cout<<"in the memory of "<<this->memPhyAd<<" disk of "<<this->diskPhyAd
    <<" and "<<(this->isWritten?"is Written":"not Writen")<<endl
    <<"Be accessed:\t"<<this->accessTimes<<" times"<<endl
    <<"recent access:\t"<<this->recentAccess
    <<endl;
}

void PageItem::reset() {
    this->inMemory = false;
    this->isWritten = false;
    this->accessTimes = -1;
    this->recentAccess = -1;
}

void PageItem::init_set() {
    this->accessTimes = 0;
    this->inMemory = true;
    this->recentAccess = ++Page_item_time;
}

void PageItem::accessed_action() {
    this->accessTimes++;
    this->recentAccess = ++Page_item_time;
}

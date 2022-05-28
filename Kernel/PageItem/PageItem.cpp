//
// Created by Zza on 2022/5/8.
//

#include "PageItem.h"
#include <iostream>


void PageItem::disp_self() const {
    using namespace std;
    cout<<"in the memory of "<<this->memPhyAd<<" disk of "<<this->diskPhyAd
    <<" and "<<(this->isWritten?"is Written":"not Writen")
    <<"; Be accessed "<<this->accessTimes<<" times"<<endl;
}

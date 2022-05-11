//
// Created by Zza on 2022/5/8.
//

#include "PageList.h"

PageList::PageList() : PageFrame() {
    this->len = PAGE_LENGTH;
    for(int i=0; i<PAGE_LENGTH; i++){
        this->list[i].diskPhyAd = i;
    }
}

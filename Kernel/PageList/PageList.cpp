//
// Created by Zza on 2022/5/8.
//

#include "PageList.h"
#include "../../Exceptions/Exception_BoundExceed.h"

PageList::PageList() : PageFrame() {
    this->len = PAGE_LENGTH;
    for(int i=0; i<PAGE_LENGTH; i++){
        this->list[i].diskPhyAd = i;
    }
}

PageItem *PageList::pageAccess(int pageId) {
    if(pageId > this->len){
        throw Exception_BoundExceed();
    }
    return &(this->list[pageId]);
}

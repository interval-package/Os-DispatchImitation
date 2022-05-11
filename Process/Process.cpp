//
// Created by Zza on 2022/5/11.
//

#include "Process.h"

PageFrame *Process::access_vir_ad(int ad) {
    int pageId = ad / this->list.len;
    int offset = ad % this->list.len;

    PageItem* tar = this->list.pageAccess(pageId);

    if(tar->inMemory){
        return this->process_mem.access_memory(tar->memPhyAd,offset);
    }else{
        throw Exception_Page_Missing(pageId);
    }
}

void Process::Dispatching() {

}

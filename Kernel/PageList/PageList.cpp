//
// Created by Zza on 2022/5/8.
//

#include "PageList.h"
#include "../../Exceptions/Exception_BoundExceed.h"

PageList::PageList() : PageFrame() {
//    使用默认长度进行初始化
    this->len = LIST_LENGTH;
//    默认使用，顺序存储的地址信息
    for(int i=0; i<this->len; i++){
        this->list[i].diskPhyAd = i;
    }
}

PageItem *PageList::pageAccess(int pageId) {
//    访问页表实例，返回页表指针
    if(pageId > this->len){
//        当访问超出允许的位置，抛出异常
        throw Exception_BoundExceed();
    }
    return &(this->list[pageId]);
}

PageList::PageList(int _len): PageFrame(),len(_len) {

}

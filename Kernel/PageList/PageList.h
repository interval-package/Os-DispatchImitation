//
// Created by Zza on 2022/5/8.
//

#ifndef OS_DISPATCHIMITATION_PAGELIST_H
#define OS_DISPATCHIMITATION_PAGELIST_H

#include "../PageItem/PageItem.h"
#include "../PageFrame/PageFrame.h"

// 认为PageList也是一个页表项
class PageList:public PageFrame{
private:
    int len;
public:
    explicit PageList();
    PageItem list[PAGE_LENGTH];
};


#endif //OS_DISPATCHIMITATION_PAGELIST_H

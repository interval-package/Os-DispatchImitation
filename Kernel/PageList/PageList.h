//
// Created by Zza on 2022/5/8.
//

#ifndef OS_DISPATCHIMITATION_PAGELIST_H
#define OS_DISPATCHIMITATION_PAGELIST_H

#include "../PageItem/PageItem.h"
#include "../PageFrame/PageFrame.h"
#include "../../Exceptions/Exception_Page_Missing.h"

// 页表
// 认为PageList也是一个页表项
class PageList:public PageFrame{
public:
//    默认初始化函数，使得按照顺序向磁盘进行映射
    explicit PageList();

    explicit PageList(int _len);

    PageItem list[PAGE_LENGTH];

    int len;

    PageItem* pageAccess(int ad);

//    void randomly_init_list();

    void disp_self();

};


#endif //OS_DISPATCHIMITATION_PAGELIST_H

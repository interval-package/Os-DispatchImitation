//
// Created by Zza on 2022/5/11.
//

#ifndef OS_DISPATCHIMITATION_EXCEPTION_PAGE_MISSING_H
#define OS_DISPATCHIMITATION_EXCEPTION_PAGE_MISSING_H

#include <exception>
#include "../Kernel/PageItem/PageItem.h"

class Exception_Page_Missing: public std::exception{
public:
//    缺页中断必须要指出现在我们所希望访问的实际物理地址，用于传参

    explicit Exception_Page_Missing(PageItem *tar, int _ad, int _offset);
//    int tar_phy_ad{};

    PageItem *item;

    int block_ad;
    int offset;
//    includes the error place we try to get
    void disp_err() const;
};


#endif //OS_DISPATCHIMITATION_EXCEPTION_PAGE_MISSING_H

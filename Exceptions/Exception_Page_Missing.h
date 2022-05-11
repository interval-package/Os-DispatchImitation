//
// Created by Zza on 2022/5/11.
//

#ifndef OS_DISPATCHIMITATION_EXCEPTION_PAGE_MISSING_H
#define OS_DISPATCHIMITATION_EXCEPTION_PAGE_MISSING_H

#include <exception>

class Exception_Page_Missing: public std::exception{
public:
//    缺页中断必须要指出现在我们所希望访问的实际物理地址，用于传参
    Exception_Page_Missing(int phyAd);
    int tar_phy_ad;
};


#endif //OS_DISPATCHIMITATION_EXCEPTION_PAGE_MISSING_H

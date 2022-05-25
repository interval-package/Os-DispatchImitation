//
// Created by Zza on 2022/5/8.
//

#ifndef OS_DISPATCHIMITATION_PAGEITEM_H
#define OS_DISPATCHIMITATION_PAGEITEM_H

#include <string>
#include "../PageFrame/PageFrame.h"

class PageItem {
private:
    std::string info;
//    PageFrame* tar;
// 这里没有处理好，我们是要用什么
public:
// all the objs we must explicitly call the constructor
    explicit PageItem()= default;

// we define the length of every page frame
    const static int PageLen = 1024;
    int memPhyAd = -1;
    int diskPhyAd = -1;
    bool inMemory = false;

//    使用回写法处理
    int isWritten = false;
    int accessTimes = 0;
    int recentAccess = -1;

// level means the type of this page, if -1 it means it's page
// if level>0, it's a list
    int level = -1;
};


#endif //OS_DISPATCHIMITATION_PAGEITEM_H

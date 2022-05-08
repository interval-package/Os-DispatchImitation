//
// Created by Zza on 2022/5/8.
//

#ifndef OS_DISPATCHIMITATION_PAGEITEM_H
#define OS_DISPATCHIMITATION_PAGEITEM_H

#include <string>

class PageItem {
private:
    std::string info;
public:
// all the objs we must explicitly call the constructor
    explicit PageItem(int outer_phyAd);

// we define the length of every page frame
    const static int PageLen = 1024;
protected:
    int memPhyAd = -1;
    int diskPhyAd = -1;
    bool inMemory = false;
    int isWritten = false;
    int accessTimes = 0;
    int recentAccess = -1;

// level means the type of this page, if -1 it means it's page
// if level>0, it's a list
    const int level;
};


#endif //OS_DISPATCHIMITATION_PAGEITEM_H

//
// Created by Zza on 2022/5/9.
//

#ifndef OS_DISPATCHIMITATION_PAGEFRAME_H
#define OS_DISPATCHIMITATION_PAGEFRAME_H

#define PAGE_LENGTH 1024

class PageFrame {
public:
    int info;
    int id;

    void disp_self() const;
};


#endif //OS_DISPATCHIMITATION_PAGEFRAME_H

//
// Created by Zza on 2022/5/9.
//

#ifndef OS_DISPATCHIMITATION_DISK_H
#define OS_DISPATCHIMITATION_DISK_H

#include "../../Kernel/PageFrame/PageFrame.h"

class Disk {
private:
    int d_size;
public:
    Disk();

    PageFrame& access_disk(int);

    void write_disk(int,const PageFrame&);

    PageFrame body[];

};


#endif //OS_DISPATCHIMITATION_DISK_H

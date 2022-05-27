//
// Created by Zza on 2022/5/9.
//

#ifndef OS_DISPATCHIMITATION_DISK_H
#define OS_DISPATCHIMITATION_DISK_H

#include "../../Kernel/PageFrame/PageFrame.h"

class Disk {
private:

    static const int INIT_DISK_SIZE = 2048;

    int d_size = INIT_DISK_SIZE;
    PageFrame body[INIT_DISK_SIZE]{};

public:
    Disk();

//    获得磁盘页面实例，当调入内存时使用
    PageFrame &get_disk_frame_instance(int ad);

    void write_disk_frame(int ad, const PageFrame &frame);



};


#endif //OS_DISPATCHIMITATION_DISK_H

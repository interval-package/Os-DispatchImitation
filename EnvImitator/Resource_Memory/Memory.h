//
// Created by Zza on 2022/5/9.
//

#ifndef OS_DISPATCHIMITATION_MEMORY_H
#define OS_DISPATCHIMITATION_MEMORY_H

#include "../../Kernel/PageFrame/PageFrame.h"
#include <vector>

class Memory {
public:
    static const int INIT_MEMORY_SIZE = 128;

    Memory();

    std::vector<int> free_set;

    PageFrame *access_memory(int phy_ad, int offset);

    void write_mem_frame(int phy_ad, const PageFrame &tar);

//    申请新的内存块
    int req_new_mem();

//    获得某个特定块的实例，用于写回操作
    PageFrame& get_mem_frame_instance(int ad);

//    ~Memory();
private:
    int m_size = INIT_MEMORY_SIZE;
    PageFrame body[INIT_MEMORY_SIZE]{};
};


#endif //OS_DISPATCHIMITATION_MEMORY_H

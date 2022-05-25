//
// Created by Zza on 2022/5/9.
//

#ifndef OS_DISPATCHIMITATION_MEMORY_H
#define OS_DISPATCHIMITATION_MEMORY_H

#include "../../Kernel/PageFrame/PageFrame.h"
#include <vector>

class Memory {
private:
    static const int INIT_MEMORY_SIZE = 128;
    int m_size = INIT_MEMORY_SIZE;
    PageFrame body[INIT_MEMORY_SIZE]{};
public:
    Memory();

    std::vector<int> free_set;

    PageFrame *access_memory(int phy_ad, int offset);

    void write_mem_frame(int phy_ad, const PageFrame &tar);

    int req_new_mem();

    void return_mem(int ad);

//    ~Memory();
};


#endif //OS_DISPATCHIMITATION_MEMORY_H

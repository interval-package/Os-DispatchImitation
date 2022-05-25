//
// Created by Zza on 2022/5/9.
//

#include "Memory.h"

PageFrame *Memory::access_memory(int phy_ad, int offset) {
    return nullptr;
}

void Memory::write_mem_frame(int phy_ad, const PageFrame &tar) {
    this->body[phy_ad] = tar;
}

Memory::Memory() {
    for (int i = 0; i < Memory::INIT_MEMORY_SIZE; ++i) {
        this->free_set.push_back(i);
    }
}

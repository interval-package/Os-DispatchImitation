//
// Created by Zza on 2022/5/9.
//

#include "Memory.h"
#include <iostream>

PageFrame *Memory::access_memory(int phy_ad, int offset) {
    std::cout<<"access memory at "<<phy_ad<<", with offset "<<offset<<std::endl;
    return &this->body[phy_ad];
}

void Memory::write_mem_frame(int phy_ad, const PageFrame &tar) {
    this->body[phy_ad] = tar;
}

Memory::Memory() {
    for (int i = 0; i < Memory::INIT_MEMORY_SIZE; ++i) {
        this->free_set.push_back(i);
    }
}

int Memory::req_new_mem() {
    int temp = this->free_set.back();
    this->free_set.pop_back();
    return temp;
}

PageFrame &Memory::get_mem_frame_instance(int ad) {
    return this->body[ad];
}

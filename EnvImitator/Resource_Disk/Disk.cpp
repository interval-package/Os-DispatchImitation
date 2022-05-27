//
// Created by Zza on 2022/5/9.
//

#include "Disk.h"

Disk::Disk() {
    for(int i=0; i<this->d_size; i++){
        this->body[i].id = i;
    }
}

PageFrame &Disk::get_disk_frame_instance(int ad) {
    return this->body[ad];
}

void Disk::write_disk_frame(int ad, const PageFrame &frame) {
    this->body[ad] = frame;
}

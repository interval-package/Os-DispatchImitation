//
// Created by Zza on 2022/5/9.
//

#include "Disk.h"

Disk::Disk() {
    this->d_size = PAGE_LENGTH;
    for(int i=0; i<this->d_size; i++){
        this->body[i].id = i;
    }
}

//
// Created by Zza on 2022/5/9.
//

#ifndef OS_DISPATCHIMITATION_MEMORY_H
#define OS_DISPATCHIMITATION_MEMORY_H

#include "../../Kernel/PageFrame/PageFrame.h"

class Memory {
private:
    int m_size;
    PageFrame body[];

public:
    Memory(int);

    void access_memory(int,int);

    void exchange_frame(int,const PageFrame&);

    ~Memory();
};


#endif //OS_DISPATCHIMITATION_MEMORY_H

//
// Created by Zza on 2022/5/11.
//

#ifndef OS_DISPATCHIMITATION_PROCESS_H
#define OS_DISPATCHIMITATION_PROCESS_H

#include "../EnvImitator/Resource_Memory/Memory.h"
#include "../EnvImitator/Resource_Disk/Disk.h"

#include "../DispatchAction/DispatchAction.h"

#include "../Kernel/PageLinkedList/PageLinkedList.h"
#include "../Kernel/PageList/PageList.h"

class Process {
private:
    Memory process_mem;
    Disk process_disk;

    PageList list;
    PageLinkedList page_set;
public:

    PageFrame* access_vir_mem(int ad);



};


#endif //OS_DISPATCHIMITATION_PROCESS_H

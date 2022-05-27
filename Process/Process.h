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

typedef std::vector<int> ACTIONS;

class Process {
public:

    int mem_valid_size = 64;

    Process(Memory *mem, Disk *disk, int WorkSpace);

    PageFrame* access_vir_ad(int pageId);

    void run(ACTIONS &tar);

    void run();

private:
    PageList list;
//    使用页框链表，用于后续的调度算法
    PageLinkedList page_set;

//    获得对应的指针，内存指针应当有两个备份。
    Memory* process_mem;
    Disk* process_disk;

    void dispatching(Exception_Page_Missing& e);

//    使用页表项作为媒介，将内存内部的信息写入
    void write_mem_to_disk(PageItem* mem_item);

    void write_disk_to_mem(PageItem* old_mem, PageItem* new_mem);
};


#endif //OS_DISPATCHIMITATION_PROCESS_H

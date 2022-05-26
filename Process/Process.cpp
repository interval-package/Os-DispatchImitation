//
// Created by Zza on 2022/5/11.
//

#include <iostream>
#include "Process.h"
#include <ctime>

PageFrame *Process::access_vir_ad(int ad) {
//    返回值实际上没有用
    int pageId = ad / this->list.len;
    int offset = ad % this->list.len;

    PageItem* tar = this->list.pageAccess(pageId);

    if(tar->inMemory){
//        访问的实际结果在这里，在access_memory里面进行打印
        tar->accessTimes++;
//        tar->recentAccess =
        return this->process_mem->access_memory(tar->memPhyAd, offset);
    }else{
        throw Exception_Page_Missing(pageId, 0);
    }
}

Process::Process(Memory *mem, Disk *disk, int WorkSpace) :
process_mem(mem),process_disk(disk),page_set(WorkSpace,mem)
{
}

void Process::run(ACTIONS &tar) {
    using namespace std;
    for (auto iter: tar) {
        cout<<"now is to access: "<<iter<<endl;
        try{
            this->access_vir_ad(iter);
        }
        catch (Exception_Page_Missing& e) {
            e.disp_err();
            this->dispatching(e);
        }
    }
}

void Process::dispatching(Exception_Page_Missing &e) {
    using namespace std;
    cout<<"start dispatching"<<endl;
    PageItem* temp = this->list.pageAccess(e.block_ad);

//    进行调度，将被调度页的页表项换出
    temp = this->page_set.dispatching(temp);

//    调用写回策略
    if(temp->isWritten){
        this->write_mem_disk(temp);
    }
}

void Process::write_mem_disk(PageItem *mem_item) {
//    该函数要为内存与磁盘的友元函数，可以直接访问替换
    PageFrame temp = this->process_mem->return_mem(mem_item->memPhyAd);
    this->process_disk->write_disk(mem_item->diskPhyAd, temp);
}

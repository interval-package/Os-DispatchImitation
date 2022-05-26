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
        throw Exception_Page_Missing(tar, pageId, offset);
    }
}

Process::Process(Memory *mem, Disk *disk, int WorkSpace) :
process_mem(mem),process_disk(disk),page_set(WorkSpace,mem)
{
}

void Process::run(ACTIONS &tar) {
    using namespace std;
    PageFrame* temp;
    for (auto iter: tar) {
        cout<<"now is to access: "<<iter<<endl;
        try{
//            尝试访问虚拟地址，如果访问成功则打印虚拟地址内容
            temp = this->access_vir_ad(iter);
            temp->disp_self();
        }
        catch (Exception_Page_Missing& e) {
//            打印错误，然后进入调度算法
            e.disp_err();
            this->dispatching(e);
        }
    }
}

void Process::dispatching(Exception_Page_Missing &e) {
    using namespace std;
    cout<<"start dispatching"<<endl;

//    获取传递来的，中断失败页表项
    PageItem* temp = e.item;

//    进行调度，将被调度页的页表项换出，使用链表内部的调度算法
    PageItem *old = this->page_set.dispatching(temp);

//    调用写回策略，如果有修改就写回磁盘
    if(old->isWritten){
        this->write_mem_to_disk(old);
        old->isWritten = false;
    }

    write_disk_to_mem(old, temp);

//    修改内容，将目标页表项的内容，修改到
    old->inMemory = false;
    temp->inMemory = true;

}

void Process::write_mem_to_disk(PageItem *mem_item) {
//    该函数要为内存与磁盘的友元函数，可以直接访问替换
    PageFrame temp = this->process_mem->return_mem(mem_item->memPhyAd);
    this->process_disk->write_disk(mem_item->diskPhyAd, temp);
}

void Process::write_disk_to_mem(PageItem *old_mem, PageItem *new_mem) {
    PageFrame temp = this->process_disk->access_disk(new_mem->diskPhyAd);
    this->process_mem->write_mem_frame(old_mem->memPhyAd,temp);
}

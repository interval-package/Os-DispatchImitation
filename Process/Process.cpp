//
// Created by Zza on 2022/5/11.
//

#include <iostream>
#include "Process.h"

PageFrame *Process::access_vir_ad(int ad) {
//    返回值实际上没有用
    int pageId = ad / this->list.len;
    int offset = ad % this->list.len;

    PageItem* tar = this->list.pageAccess(pageId);

    if(tar->inMemory){
//        访问的实际结果在这里，在access_memory里面进行打印
        return this->process_mem->access_memory(tar->memPhyAd, offset);
    }else{
        throw Exception_Page_Missing(pageId);
    }
}

void Process::Dispatching() {

}

Process::Process(Memory *mem, Disk *disk, int WorkSpace) :
process_mem(mem),process_disk(disk),page_set(WorkSpace,mem)
{
}

void Process::run(ACTIONS &tar) {
    using namespace std;
    for (auto iter: tar) {
        cout<<"now is to access: "<<iter<<endl;
        this->access_vir_ad(iter);
    }
}

//
// Created by Zza on 2022/5/11.
//

#include <iostream>
#include "Process.h"
#include <ctime>

// 自动分配的全局化id
int global_id = 0;

PageFrame *Process::access_vir_ad_R(int ad) {
//    返回值实际上没有用
    int pageId = ad / PageFrame::PAGE_LENGTH;
    int offset = ad % PageFrame::PAGE_LENGTH;

    PageItem* tar = this->list.pageAccess(pageId);

    if(tar->inMemory){
//        访问的实际结果在这里，在access_memory里面进行打印
        tar->accessed_action();
        tar->disp_self();
        return this->process_mem->access_memory(tar->memPhyAd, offset);
    }else{
        throw Exception_Page_Missing(tar, pageId, offset);
    }
}

PageFrame *Process::access_vir_ad_RW(int ad, bool is_write) {
//    返回值实际上没有用
    int pageId = ad / PageFrame::PAGE_LENGTH;
    int offset = ad % PageFrame::PAGE_LENGTH;

    PageItem* tar = this->list.pageAccess(pageId);

    if(tar->inMemory){
//        访问的实际结果在这里，在access_memory里面进行打印
        tar->accessed_action();
        tar->disp_self();
        return this->process_mem->access_memory(tar->memPhyAd, offset);
    }else{
        throw Exception_Page_Missing(tar, pageId, offset);
    }
}


Process::Process(Memory *mem, Disk *disk, int workspace_size) :
process_mem(mem),process_disk(disk),page_set(workspace_size, mem),id(global_id)
{
    std::cout<<"init process with global_id = "<<global_id++<<std::endl;
}

void Process::run(ACTIONS &tar) {
    using namespace std;
    PageFrame* temp;
    for (auto iter: tar) {
        cout<<"now is to access: "<<iter<<endl;
        try{
//            尝试访问虚拟地址，如果访问成功则打印虚拟地址内容
            temp = this->access_vir_ad_R(iter);
        }
        catch (Exception_Page_Missing& e) {
//            打印错误，然后进入调度算法
            e.disp_err();
//            调度过后默认会进行访问
            this->dispatching(e);
//            this->page_set.display_cur();
            temp = this->access_vir_ad_R(iter);
        }
        cout<<"--------------------------"<<endl;
    }
    this->page_set.display_cur();
}

void Process::run() {
    using namespace std;
    PageFrame* temp;

    int instruction;

    cout<<"please input your tar ad(minus ad will redirect to commands): ";

    while (cin>>instruction) {

        if(instruction == 0) break;

        if (instruction<0){
            if(instruction>=-5){
                this->page_set.display_cur();
                continue;
            } else{
                this->single_step(-instruction, true);
            }
        }

        cout<<"now is to access: "<<instruction<<endl;
        try{
//            尝试访问虚拟地址，如果访问成功则打印虚拟地址内容
            temp = this->access_vir_ad_R(instruction);
            temp->disp_self();
        }
        catch (Exception_Page_Missing& e) {
//            打印错误，然后进入调度算法
            e.disp_err();
            this->dispatching(e);

            temp = this->access_vir_ad_R(instruction);
        }
        catch (Exception_BoundExceed& e) {
            cout<<"access invalid ad!"<<endl;
        }
        cout<<"--------------------------"<<endl;
        cout<<"please input your tar ad: ";
    }
}

void Process::single_step(int ad, bool is_write) {
    using namespace std;

    PageFrame* temp;

    cout<<"now is to access: "<<ad<<endl;
    try{
//            尝试访问虚拟地址，如果访问成功则打印虚拟地址内容
        temp = this->access_vir_ad_RW(ad, is_write);
        temp->disp_self();
    }
    catch (Exception_Page_Missing& e) {
//            打印错误，然后进入调度算法
        e.disp_err();
        this->dispatching(e);
    }
    catch (Exception_BoundExceed& e) {
        cout<<"access invalid ad!"<<endl;
    }
}

void Process::dispatching(Exception_Page_Missing &e) {
    using namespace std;
    cout<<"start dispatching"<<endl;

//    获取传递来的，中断失败页表项
    PageItem* temp = e.item;

//    进行调度，将被调度页的页表项换出，使用链表内部的调度算法
    PageItem *old = this->page_set.inner_dispatching(temp);

//    如果是新加页,则会返回一个空指针
    if(!old){
//        若为空指针,则不进行新的调度,直接写入
//        应该写个接口的,但是这里还是先直接实现吧

        int new_ad = this->process_mem->req_new_mem();
        temp->memPhyAd = new_ad;
        this->write_disk_to_mem(temp,temp);

        temp->init_set();
        this->process_mem->access_memory(temp->memPhyAd,e.offset);
        return;
    }

//    调用写回策略，如果有修改就写回磁盘
    if(old->isWritten){
        cout<<"dirty frame, write back."<<endl;
        this->write_mem_to_disk(old);
        old->isWritten = false;
    }

    cout<<"get old frame at "<<old->memPhyAd<<endl;
    temp->memPhyAd = old->memPhyAd;
    write_disk_to_mem(old, temp);

//    修改内容，将目标页表项的内容，修改到
    old->reset();
    temp->init_set();

//    this->process_mem->access_memory(temp->memPhyAd,e.offset);
}

void Process::write_mem_to_disk(PageItem *mem_item) {
//    该函数要为内存与磁盘的友元函数，可以直接访问替换
    PageFrame temp = this->process_mem->get_mem_frame_instance(mem_item->memPhyAd);
    this->process_disk->write_disk_frame(mem_item->diskPhyAd, temp);
}

void Process::write_disk_to_mem(PageItem *old_mem, PageItem *new_mem) {
    std::cout<<"write disk at "<<new_mem->diskPhyAd<<" to mem at "<<old_mem->memPhyAd<<std::endl;
    PageFrame temp = this->process_disk->get_disk_frame_instance(new_mem->diskPhyAd);
    this->process_mem->write_mem_frame(old_mem->memPhyAd,temp);
}

void Process::set_dispatch_type(char type) {
    this->page_set._dsp_type = type;
}




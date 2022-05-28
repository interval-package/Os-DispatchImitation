//
// Created by Zza on 2022/5/9.
//

#ifndef OS_DISPATCHIMITATION_PAGEFRAME_H
#define OS_DISPATCHIMITATION_PAGEFRAME_H



class PageFrame {
public:
    static const int PAGE_LENGTH=1024;
//    explicit PageFrame(int _id, int _info=0);
    int info = 0;
    int id =0;

    void disp_self() const;
};


#endif //OS_DISPATCHIMITATION_PAGEFRAME_H

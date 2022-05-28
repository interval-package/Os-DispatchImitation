//
// Created by Zza on 2022/5/11.
//

#include "Exception_Page_Missing.h"
#include <iostream>

void Exception_Page_Missing::disp_err() const {
    std::cout << "Page missing break! at block " << this->block_ad << std::endl;
}

Exception_Page_Missing::Exception_Page_Missing(PageItem *tar, int _ad, int _offset)
: item(tar), block_ad(_ad), offset(_offset) {
}

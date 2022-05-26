//
// Created by Zza on 2022/5/11.
//

#include "Exception_Page_Missing.h"
#include <iostream>

void Exception_Page_Missing::disp_err() const {
    std::cout << "Page missing break! at " << this->block_ad << std::endl;
}

Exception_Page_Missing::Exception_Page_Missing(int _block_ad, int _offset)
: block_ad(_block_ad), offset(_offset) {

}

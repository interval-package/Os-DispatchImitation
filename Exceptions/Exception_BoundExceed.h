//
// Created by Zza on 2022/5/8.
//

#ifndef OS_DISPATCHIMITATION_EXCEPTION_BOUNDEXCEED_H
#define OS_DISPATCHIMITATION_EXCEPTION_BOUNDEXCEED_H

#include <exception>
#include <string>
#include <iostream>

class Exception_BoundExceed:public std::exception {
    explicit Exception_BoundExceed(const char* msg = "bound exceed"){
        std::cerr<<msg<<std::endl;
    }
};


#endif //OS_DISPATCHIMITATION_EXCEPTION_BOUNDEXCEED_H

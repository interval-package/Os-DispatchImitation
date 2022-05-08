cmake_minimum_required(VERSION 3.21)
project(Os_DispatchImitation)

set(CMAKE_CXX_STANDARD 14)

add_executable(Os_DispatchImitation main.cpp Kernel/PageList/PageList.cpp Kernel/PageList/PageList.h Kernel/Page/Page.cpp Kernel/Page/Page.h Kernel/PageLinkedList/PageLinkedList.cpp Kernel/PageLinkedList/PageLinkedList.h Kernel/DispatchAction/DispatchAction.cpp Kernel/DispatchAction/DispatchAction.h)

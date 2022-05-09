cmake_minimum_required(VERSION 3.21)
project(Os_DispatchImitation)

set(CMAKE_CXX_STANDARD 14)

add_executable(
        Os_DispatchImitation main.cpp

        Kernel/PageList/PageList.cpp Kernel/PageList/PageList.h
        Kernel/PageItem/PageItem.cpp Kernel/PageItem/PageItem.h
        Kernel/PageLinkedList/PageLinkedList.cpp Kernel/PageLinkedList/PageLinkedList.h
        Kernel/PageFrame/PageFrame.cpp Kernel/PageFrame/PageFrame.h

        Kernel/DispatchAction/DispatchAction.cpp Kernel/DispatchAction/DispatchAction.h

        Exceptions/Exception_BoundExceed.cpp Exceptions/Exception_BoundExceed.h
        Exceptions/Exception_NoSuchFrame.cpp Exceptions/Exception_NoSuchFrame.h


        EnvImitator/Resource_Memory/Memory.cpp EnvImitator/Resource_Memory/Memory.h EnvImitator/Resource_Disk/Disk.cpp EnvImitator/Resource_Disk/Disk.h)

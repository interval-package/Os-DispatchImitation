cmake_minimum_required(VERSION 3.21)
project(Os_DispatchImitation)

set(CMAKE_CXX_STANDARD 14)

add_executable(
        Os_DispatchImitation main.cpp

        Kernel/PageList/PageList.cpp Kernel/PageList/PageList.h
        Kernel/PageItem/PageItem.cpp Kernel/PageItem/PageItem.h
        Kernel/PageLinkedList/PageLinkedList.cpp Kernel/PageLinkedList/PageLinkedList.h
        Kernel/PageFrame/PageFrame.cpp Kernel/PageFrame/PageFrame.h

        Process/Process.h Process/Process.cpp

        Exceptions/Exception_BoundExceed.cpp Exceptions/Exception_BoundExceed.h
        Exceptions/Exception_NoSuchFrame.cpp Exceptions/Exception_NoSuchFrame.h
        Exceptions/Exception_Page_Missing.cpp Exceptions/Exception_Page_Missing.h

        EnvImitator/Resource_Memory/Memory.cpp EnvImitator/Resource_Memory/Memory.h
        EnvImitator/Resource_Disk/Disk.cpp EnvImitator/Resource_Disk/Disk.h

        Threading_Pack/Thread_Proc_Wrapper.cpp Threading_Pack/Thread_Proc_Wrapper.h
        Threading_Pack/banker.cpp Threading_Pack/banker.h)

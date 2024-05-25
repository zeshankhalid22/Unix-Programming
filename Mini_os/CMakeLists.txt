cmake_minimum_required(VERSION 3.28)
project(naqli_os)

set(CMAKE_CXX_STANDARD 17)

add_executable(naqli_os main.cpp
        include/PCB.h
        include/process_management.h
        include/scheduler.h
        include/shell.h
        shell.cpp
        process_management.cpp
        schedular.cpp
        scripts/my_commands.cpp
        include/my_commands.h
        include/global_files.h
        include/mem_map.h
        mem_map.cpp
        data.txt
)


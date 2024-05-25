# Mini OS

Mini OS is a project that simulates the working of an operating system. It is written in C/C++.

## Features

- Process creation and management
- Command execution
- Process scheduling
- Memory mapping

# Concepts Used
Utilized MultiThreading, Multiprocessing, Process Scheduling
Inter-Process Communication, Mutual Exclusion, Shell Scripting, Build System(CMake)
Custom Memory Mapping, Process logging

## How it works

### Splash Screen
The Mini os start with a sort os splash screen which is a script written
in python displays author names and instructor name.
you can comment it out in the very after line of main function.

### Process Creation and Management

The system creates a standalone process from menu given and adds it to a priority queue. Each process is represented by a Process Control Block (PCB).
Binary files of the processes(from /proc) are added in /bin. in order to update/add
a process, you need to manually put binary file of that process in /bin and add to process_management.cpp menu.
### Command Execution

The system can execute bash commands.

### Process Scheduling

The system uses a scheduling algorithm to manage the execution of processes based on their priority.

### Memory Mapping

The system uses memory mapping to map a file into the process's virtual memory space. The user can specify the address where they want to locate the memory.

## Dependencies
`Python3` for Splash Screen script
<br>`Alacritty` Terminal
<br> `vlc` for media player
<br> Other utilities used as process  `figlet`, `neofetch`, `cmatrix`, `htop`, `sl`

## Contributing

Contributions are welcome. Please open an issue or submit a pull request.

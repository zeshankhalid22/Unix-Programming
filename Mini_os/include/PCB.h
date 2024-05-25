#ifndef NAQLI_OS_PCB_H
#define NAQLI_OS_PCB_H

#include <iostream>
#include <vector>
using namespace std;


class PCB {
public:
    char *name;
    int id;
    int priority;
    bool isRunning;
    // location of the binary
    vector<string> thread_binaries;
};

#endif //NAQLI_OS_PCB_H
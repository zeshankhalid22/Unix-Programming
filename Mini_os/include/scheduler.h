#ifndef NAQLI_OS_SCHEDULER_H
#define NAQLI_OS_SCHEDULER_H

#include <queue>
#include "PCB.h"

void runProcess(PCB* pcb);

// Custom comparator for the priority queue
struct ComparePriority {
    bool operator()(PCB* const& p1, PCB* const& p2) {
        // return "true" if "p1" is ordered before "p2", for example:
        return p1->priority < p2->priority;
    }
};

void schedule(priority_queue<PCB *, vector<PCB *>, ComparePriority> &pq, int i);

#endif //NAQLI_OS_SCHEDULER_H
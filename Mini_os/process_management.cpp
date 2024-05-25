#include <iostream>
#include <chrono>
#include <iomanip>
#include "include/PCB.h"
#include "include/global_files.h"

using namespace std;

void list_proccese() {
    cout << "List of processes\n";
    cout << "1. Client Server\n";
    cout << "2. Producer_Consumer\n";
    cout << "3. Play Music\n";
    cout << "4. System Monitor\n";
    cout << "5. ls typo\n";
    cout << "6. Neofetch\n";
    cout << "7. Cmatrix\n";
    cout << "8. Figlet\n";
    cout << "9. asciiquarium\n";
}

PCB *add_process() {
    list_proccese();

    int id, priority;
    cout << "Enter Process (ID, Priority) > ";
    cin >> id >> priority;

    // Initialize the PCB
    PCB *pcb = new PCB;
    pcb->id = id;
    pcb->isRunning = false;

    log_mutex.lock();
    // Write a log entry when a process is added to the priority queue
    auto now = chrono::system_clock::now();
    auto currentTime = chrono::system_clock::to_time_t(now);
    logFile << "Process " << id << " added to the priority queue at "
            << std::put_time(std::localtime(&currentTime), "%H:%M:%S") << std::endl;
    log_mutex.unlock();

    // add process in queue
    if (id == 1) {
        pcb->name = "Client Server";
        pcb->isRunning = false;
        pcb->thread_binaries.emplace_back("../bin/./client");
        pcb->thread_binaries.emplace_back("../bin/./server");
    } else if (id == 2) {
        pcb->name = "Producer Consumer";
        pcb->isRunning = false;
        pcb->thread_binaries.emplace_back("../bin/prod_cons");
    } else if (id == 3) {
        pcb->name = "Play Music";
        pcb->isRunning = false;
        pcb->thread_binaries.emplace_back("../bin/play_music");
    } else if (id == 4) {
        pcb->name = "System Monitor";
        pcb->isRunning = false;
        pcb->thread_binaries.emplace_back("/usr/bin/htop");
    } else if (id == 5) {
        pcb->name = "sl";
        pcb->isRunning = false;
        pcb->thread_binaries.emplace_back("/usr/bin/sl");
    } else if (id == 6) {
        pcb->name = "Neofetch";
        pcb->isRunning = false;
        pcb->thread_binaries.emplace_back("/usr/bin/neofetch");
    } else if (id == 7) {
        pcb->name = "Cmatrix";
        pcb->isRunning = false;
        pcb->thread_binaries.emplace_back("/usr/bin/cmatrix");
    } else if (id == 8) {
        pcb->name = "Figlet";
        pcb->isRunning = false;
        pcb->thread_binaries.emplace_back("/usr/bin/figlet");
    } else if (id == 9) {
        pcb->name = "asciiquarium";
        pcb->isRunning = false;
        pcb->thread_binaries.emplace_back("/usr/bin/asciiquarium");
    } else {
        cout << "Invalid process number" << endl;
        delete pcb;
        return nullptr;
    }
    return pcb;
}

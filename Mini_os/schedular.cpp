#include <unistd.h>
#include <sys/wait.h>
#include <atomic>
#include <thread>
#include <fstream>
#include <chrono>
#include <iomanip>
#include "include/scheduler.h"
#include "include/global_files.h"

using namespace std;

// keep track of currently running processes
atomic<int> running_processes(0);


ofstream logFile("../log.txt", ios::app);

void runProcess(PCB *pcb) {
    // Save the start time of the process
    log_mutex.lock();
    auto start = chrono::system_clock::now();
    auto startTime = chrono::system_clock::to_time_t(start);
    logFile << "Process " << pcb->id << " started running at " << put_time(localtime(&startTime), "%H:%M:%S")
            << endl;
    log_mutex.unlock();

    for (const auto &binary: pcb->thread_binaries) {
        pid_t pid = fork();

        if (pid == 0) { // Child process
            char *terminal = {"/usr/bin/alacritty"};
            char *terminal_args[] = {terminal, "-e", const_cast<char *>(binary.c_str()), NULL};
            execv(terminal, terminal_args);
            exit(0); // Exit child process after execv returns
        }
        auto end = chrono::system_clock::now();
        auto endTime = chrono::system_clock::to_time_t(end);
        logFile << "Process " << pcb->id << " finished running at "
                << put_time(localtime(&endTime), "%H:%M:%S") << endl;
    }

    // Parent process waits for all child processes to finish
    while (wait(NULL) > 0);

    // Decrement the number of running processes
    running_processes--;
}

void schedule(priority_queue<PCB *, vector<PCB *>,
        ComparePriority> &pq, int cores) {

    while (!pq.empty()) { // spin lock
// If there are less running processes than cores, start a new process
        if (running_processes < cores) {
            PCB *pcb = pq.top();
            pq.pop();
            // run pcb in new thread execution
            thread(runProcess, pcb).detach();
            running_processes++;
        }
    }
// Wait for all processes to finish
    while (running_processes > 0);
}
#include <iostream>
#include <queue>
#include "include/PCB.h"
#include "include/shell.h"
#include "include/process_management.h"
#include "include/scheduler.h"
#include "include/global_files.h"
#include "include/mem_map.h"

using namespace std;

mutex log_mutex;

void createStandaloneProcess(priority_queue<PCB *, vector<PCB *>, ComparePriority> &pq) {
    // Add a new Process
    PCB *pcb = add_process();
    if (pcb != nullptr) {
        pq.push(pcb);
    }
}

void runCommand() {
    command_menu();
}

void showProcesses(priority_queue<PCB *, vector<PCB *>, ComparePriority> &pq) {
    // display processes
    cout << "All the processes in the queue are: ";
    while (!pq.empty()) {
        cout << pq.top()->id << " ";
        pq.pop();
    }
    cout << endl;

}

void runSchedulingAlgorithm(priority_queue<PCB *, vector<PCB *>, ComparePriority> &pq, int cores) {
    cout << "Process Scheduling ...\n ";
    cout << "-------------------------------\n";
    schedule(pq, cores);
}

void memoryMapping() {
    mem_to_file_map();
}

int main() {

    // running startup
    system("alacritty -e bash -c 'python3 ../scripts/init.py; exec bash'");

    // Create a priority queue of PCB pointers
    priority_queue<PCB *, vector<PCB *>, ComparePriority> pq;

    int cores = 1;
    cout << "How many Cores > ";
    cin >> cores;

    int choice;

    do {
        cout << "\n1. Create a standalone process" << endl;
        cout << "2. Run a command" << endl;
        cout << "3. Show all the processes" << endl;
        cout << "4. Run Scheduling Algorithm" << endl;
        cout << "5. Memory Mapping" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice > ";
        cin >> choice;

        if (choice > 6 || choice < 1) {
            cout << "Invalid choice" << endl;
            continue;
        }

        switch (choice) {
            case 1:
                createStandaloneProcess(pq);
                break;
            case 2:
                // do run bash command
                runCommand();
                break;
            case 3:
                showProcesses(pq);
                break;
            case 4:
                runSchedulingAlgorithm(pq, cores);
                break;
            case 5:
                memoryMapping();
                break;
            case 6:
                cout << "Exiting the program" << endl;
                break;
            default:
                cout << "Invalid choice" << endl;
                break;
        }
    } while (choice != 6);
    logFile.close();
    return 0;
}
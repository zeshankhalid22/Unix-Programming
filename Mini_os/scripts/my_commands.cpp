#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

void run_ls() {
    pid_t pid = fork();

    if (pid < 0) {
        // Fork failed
        cout << "Fork failed.\n";
        return;
    }
    else if (pid == 0) {
        char path[30];
        char flag[5];
        cout << "Enter the directory path > ";
        cin.ignore();
        cin.getline(path, sizeof(path));
        cout << "Enter output flag > ";
        cin.getline(flag, sizeof(flag));
        // Child process
        char *args[] = {"/bin/ls", flag, path, NULL};
        execvp(args[0], args);

    } else {
        int status;
        waitpid(pid, &status, 0);
    }
}
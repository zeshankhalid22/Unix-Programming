// in child process, the program will replace itself with "ls " and save the output in pipe
// the parent process will read from pipe and replace itself with sort command, 

#include <stdio.h>
#include <unistd.h>

int main(void) {
    pid_t childpid;
    int fd[2];
    if ((pipe(fd) == -1) || ((childpid = fork()) == -1)) {
        perror("Failed to setup pipeline");
        return 1;
    }
    // * ls is the child process
    if (childpid == 0) {
        printf("Child process started . . .\n");
        // redirect standard output to write end of fd
        if (dup2(fd[1], STDOUT_FILENO) == -1)
            perror("Failed to redirect stdout of ls");

        else if ((close(fd[0]) == -1) || (close(fd[1]) == -1))
            perror("Failed to close extra pipe descriptors on ls");

        else {
            // current process image is replaced with new process image
            execl("/bin/ls", "ls", "/home/zeshan22/", NULL);
            perror("Failed to exec ls");
        }
        return 1;
    }

        // * sort is the parent
    else {
        printf("Parent process started . . .\n");
        // anything read by standard input will be redirected
        // to fd[0]
        if (dup2(fd[0], STDIN_FILENO) == -1)
            perror("Failed to redirect stdin of sort");


        else if ((close(fd[0]) == -1) || (close(fd[1]) == -1))
            perror("Failed to close extra pipe file descriptors on sort");

        else {
            printf("Sorting . . .\n");
            // replace new image(sort ..) with current process
            execl("/bin/sort", "sort", "-n", "+4", NULL);
            perror("Failed to exec sort");
        }
        return 1;
    }

}


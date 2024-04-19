#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void handle_sigusr1(int sig) {
    printf("Received SIGUSR1! indicates Child process has finished computation.\n");
    printf("Handling the completion of child's task\n");
    sleep(2);
    printf("Parent process completed.\n");
    exit(0);
}

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }

    if (pid == 0) {
        // Child process
        printf("Child process is doing some computation...\n");
        sleep(5);  // Simulate a long computation
        printf("Child process has finished computation, sending signal to parent.\n");
        kill(getppid(), SIGUSR1);  // Send signal to parent process
    } else {
         // when parent receives a SIGUSR1 signal,
         // it will call the handle_sigusr1 function.
        signal(SIGUSR1, handle_sigusr1);
        printf("Parent process is doing some work...\n");

        // Parent process doing their computing while child is also doing its.
        while (1) {
            printf("p...\n");
            sleep(1);  // Simulate doing some work
        }
    }

    return 0;
}

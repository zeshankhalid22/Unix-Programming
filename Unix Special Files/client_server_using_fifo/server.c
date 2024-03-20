#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

int main() {
    int client_to_server;
    char *myfifo = "/tmp/client_to_server_fifo";

    int server_to_client;
    char *myfifo2 = "/tmp/server_to_client_fifo";

    char buf[BUFSIZ];
    int num1, num2;

    /* create the FIFO (named pipe) */
    mkfifo(myfifo, 0666);
    mkfifo(myfifo2, 0666);


    printf("Server ON.\n");

    while (1) {
        /* open, read, and display the message from the FIFO */
        // open myfifo in read-mode, wait until we can't open
        client_to_server = open(myfifo, O_RDONLY);
        server_to_client = open(myfifo2, O_WRONLY);
        // read data from client_to_server(fd) to > buf[]
        read(client_to_server, buf, BUFSIZ);
        read(client_to_server, &num1, sizeof(num1));
        read(client_to_server, &num2, sizeof(num2));

        if (strcmp("exit", buf) == 0) {
            printf("Server OFF.\n");
            break;
        } else if (strcmp("", buf) != 0) {
            printf("Received: %s\n", buf);
            printf("Also Received  %d, %d\n", num1, num2);
            printf("Sending back the sum...\n");
            int sum = num1 + num2;
            write(server_to_client, &sum, sizeof(sum));
        }

        /* clean buf from any data */
        memset(buf, 0, sizeof(buf));
    }

    close(client_to_server);
    close(server_to_client);

    unlink(myfifo);
    unlink(myfifo2);
    return 0;
}

#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

int main() {
    int client_to_server;
    char *myfifo = "/tmp/client_to_server_fifo";

    int server_to_client;
    char *myfifo2 = "/tmp/server_to_client_fifo";

    char buf[BUFSIZ];
    int num1, num2;

    while (1) {
        printf("Input message to server: ");
        scanf("%s", buf);
        printf("Enter 2 numbers > ");
        scanf("%d%d", &num1, &num2);

        // open FIFO(myfifo) file with write mode,
        // open() returns a file descriptor
        client_to_server = open(myfifo, O_WRONLY);
        // write data into the file descriptor
        write(client_to_server, buf, sizeof(buf));
        write(client_to_server, &num1, sizeof(num1));
        write(client_to_server, &num2, sizeof(num2));
        perror("Write: "); //Very crude error check

        if(strcmp("exit", buf)){
            printf("Exiting from Client.");
            break;
        }

        server_to_client = open(myfifo2, O_RDONLY);
        int sum;
        read(server_to_client, &sum, sizeof(sum));
        perror("Read: "); // Very crude error check

        printf("... sum received from the server: %d\n", sum);

    }
    // closing file descriptors
    close(client_to_server);
    close(server_to_client);

    return 0;
}

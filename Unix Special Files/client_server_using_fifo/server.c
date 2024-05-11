#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#define BUFSIZE 100

int main() {
    int client_to_server;
    char *to_server = "/tmp/client_to_server_fifo";

    int server_to_client;
    char *to_client = "/tmp/server_to_client_fifo";

    char op;
    int num1, num2;

    /* create the FIFO (named pipe) */
    mkfifo(to_server, 0666);
    mkfifo(to_client, 0666);

    printf("Server ON.\n...\n");

    while (1) {
        // open client_to_server(client request) pipe in Read Mode
        client_to_server = open(to_server, O_RDONLY);
        // open server_to_client( server response) in write mode
        server_to_client = open(to_client, O_WRONLY);

        // Read Request from Client
        read(client_to_server, &op, sizeof(op));
        read(client_to_server, &num1, sizeof(num1));
        read(client_to_server, &num2, sizeof(num2));

        if (op == 'q') {
            printf("Server OFF.\n");
            break;
        }
        else {
            printf("Client Requested: %d %c %d ?\n", num1, op, num2);
            printf("Responding ...\n");
            int result;
            switch (op) {
                case '+': result = num1 + num2; break;
                case '-': result = num1 - num2; break;
                case '*': result = num1 * num2; break;
                case '/': result = num1 / num2; break;
                case '%': result = num1 % num2; break;
                default:  result = -1;
            }
            // send response back to client
            write(server_to_client, &result, sizeof(result));
        }
    }

    close(client_to_server);
    close(server_to_client);

    unlink(to_server);
    unlink(to_client);
    return 0;
}

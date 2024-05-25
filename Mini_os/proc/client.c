#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
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

    while (1) {
        printf("Enter $op $num1 $num2 > ");
        scanf(" %c", &op);
        if (op == 'q') {
            break;
        }
        scanf("%d%d", &num1, &num2);

        // Pass Request to Server
        client_to_server = open(to_server, O_WRONLY);
        write(client_to_server, &op, sizeof(op));
        write(client_to_server, &num1, sizeof(num1));
        write(client_to_server, &num2, sizeof(num2));

        // Read response from server
        server_to_client = open(to_client, O_RDONLY);
        int result;
        read(server_to_client, &result, sizeof(result));

        printf("Response from the server: %d\n", result);
    }

    close(client_to_server);
    close(server_to_client);

    return 0;
}
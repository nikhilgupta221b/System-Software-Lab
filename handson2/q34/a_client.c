#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

#define MAX_MESSAGE_LENGTH 100

void communicate_with_server(int client_number) {
    int socketFileDescriptor;
    int connectStatus;
    struct sockaddr_in address;
    ssize_t readBytes, writeBytes;
    char dataFromServer[MAX_MESSAGE_LENGTH];
    char message[MAX_MESSAGE_LENGTH];
    socketFileDescriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (socketFileDescriptor == -1) {
        perror("Error while creating socket!");
        return;
    }
    printf("Client %d: Socket successfully created!\n", client_number);
    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_port = htons(8080);
    address.sin_addr.s_addr = INADDR_ANY;
    connectStatus = connect(socketFileDescriptor, (struct sockaddr *)&address, sizeof(address));
    if (connectStatus == -1) {
        perror("Error while connecting to the server!");
        close(socketFileDescriptor);
        return;
    }
    printf("Client %d: Connected to the server!\n", client_number);

    while (1) {
        printf("Client %d: Enter a message (type 'exit' to quit): ", client_number);
        fgets(message, sizeof(message), stdin);
        message[strlen(message) - 1] = '\0';
        writeBytes = write(socketFileDescriptor, message, strlen(message));
        if (writeBytes == -1) {
            perror("Error while writing to network via socket!");
            break;
        }
        readBytes = read(socketFileDescriptor, dataFromServer, sizeof(dataFromServer));
        if (readBytes == -1) {
            perror("Error while reading from the server!");
            break;
        } else {
            dataFromServer[readBytes] = '\0'; 
            printf("Client %d received data from the server: %s\n", client_number, dataFromServer);
        }
        if (strcasecmp(message, "exit") == 0) {
            printf("Client %d requested to exit. Closing the connection.\n", client_number);
            break;
        }
    }

    close(socketFileDescriptor);
}

int main() {
    int num_clients = 5; 

    for (int i = 1; i <= num_clients; i++) {
        pid_t pid = fork();

        if (pid == 0) {
            communicate_with_server(i);
            exit(0);
        } else if (pid < 0) {
            perror("fork returns");
            return 1;
        }
    }

    for (int i = 0; i < num_clients; i++) {
        wait(NULL);
    }

    return 0;
}

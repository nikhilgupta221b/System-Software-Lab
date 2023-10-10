#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main() {
    struct sockaddr_in serv;
    int sd;
    char buf[80];
    sd = socket(AF_INET, SOCK_STREAM, 0);
    if (sd == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = INADDR_ANY; 
    serv.sin_port = htons(3558);
    if (connect(sd, (struct sockaddr*)&serv, sizeof(serv)) == -1) {
        perror("connect");
        close(sd);
        exit(EXIT_FAILURE);
    }
    const char* message = "Hello Server\n";
    int bytes_sent = write(sd, message, strlen(message));
    if (bytes_sent == -1) {
        perror("write");
        close(sd);
        exit(EXIT_FAILURE);
    }
    int bytes_received = read(sd, buf, sizeof(buf) - 1);
    if (bytes_received == -1) {
        perror("read");
        close(sd);
        exit(EXIT_FAILURE);
    }
    buf[bytes_received] = '\0';
    printf("Message from server: %s\n", buf);
    close(sd);
    return 0;
}

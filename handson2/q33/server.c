#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main() {
    struct sockaddr_in serv, cli;
    int sd, nsd,sz;
    char buf[80];

    
    sd = socket(AF_INET, SOCK_STREAM, 0);
    if (sd == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = INADDR_ANY;
    serv.sin_port = htons(3558); 

    
    if (bind(sd, (struct sockaddr*)&serv, sizeof(serv)) == -1) {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    
    if (listen(sd, 5) == -1) { 
        perror("listen");
        exit(EXIT_FAILURE);
    }

    sz = sizeof(cli);

    
    nsd = accept(sd, (struct sockaddr*)&cli, &sz);

    
    int bytes_received = read(nsd, buf, sizeof(buf));
    if (bytes_received == -1) {
        perror("read");
        exit(EXIT_FAILURE);
    }

    buf[bytes_received] = '\0';

    printf("Message from client: %s\n", buf);

    
    const char* ack_message = "ACK from Server\n";
    int bytes_sent = write(nsd, ack_message, strlen(ack_message));
    if (bytes_sent == -1) {
        perror("write");
    }

    
    close(nsd);

    
    close(sd);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main() {

    // creating 2 fifo files
    const char *FIFO1 = "fifo_one";
    const char *FIFO2 = "fifo_two";
    mkfifo(FIFO1, 0666);
    mkfifo(FIFO2, 0666);

    char message[] = "Hi Server! Wakeup!";
    char buffer[256];
    int fd1, fd2;

    // Write message to FIFO1 for server
    fd1 = open(FIFO1, O_WRONLY);
    write(fd1, message, sizeof(message));
    close(fd1);

    // Read response from FIFO2
    fd2 = open(FIFO2, O_RDONLY);
    read(fd2, buffer, sizeof(buffer));
    printf("From Server: %s\n", buffer);
    close(fd2);

    return 0;
}


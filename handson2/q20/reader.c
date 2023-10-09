#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>



int main() {
    const char *FIFO_PATH = "nikfifo";
    char buffer[256];
    int fd;

    // Open the FIFO for reading
    fd = open(FIFO_PATH, O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Read the message from the FIFO
    read(fd, buffer, sizeof(buffer));
    printf("Message from writer: %s\n", buffer);
    close(fd);

    // Remove the FIFO after reading from it
    unlink(FIFO_PATH);

    return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main() {
    const char *FIFO_PATH = "nikfifo";
    // Create the FIFO
    mkfifo(FIFO_PATH, 0666);

    char message[] = "Hello Reader! How are you?";
    int fd;

    // Open the FIFO for writing
    fd = open(FIFO_PATH, O_WRONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Write the message to the FIFO
    write(fd, message, sizeof(message));
    close(fd);

    return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/select.h>



int main() {

    const char *FIFO_PATH = "my_fifo";
    mkfifo(FIFO_PATH, 0666); // Create the FIFO

    int fd = open(FIFO_PATH, O_RDONLY | O_NONBLOCK); // Open in non-blocking mode
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    fd_set read_fds; // Set of file descriptors to monitor
    struct timeval timeout;

    // Set up the timeout: 10 seconds
    timeout.tv_sec = 10;
    timeout.tv_usec = 0;

    FD_ZERO(&read_fds);       // Clear the set
    FD_SET(fd, &read_fds);    // Add our file descriptor to the set

    int ret = select(fd + 1, &read_fds, NULL, NULL, &timeout);

    if (ret == -1) {
        perror("select");
    } else if (ret == 0) {
        printf("No data within 10 seconds.\n");
    } else {
        if (FD_ISSET(fd, &read_fds)) {
            char buffer[256];
            int bytes = read(fd, buffer, sizeof(buffer) - 1);
            if (bytes > 0) {
                buffer[bytes] = '\0';  // Null terminate the string
                printf("Received: %s\n", buffer);
            }
        }
    }

    close(fd);
    unlink(FIFO_PATH); // Remove the FIFO

    return 0;
}


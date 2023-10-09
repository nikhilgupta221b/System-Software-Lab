#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>



int main() {
    const char *FIFO1 = "fifo_one";
    const char *FIFO2 = "fifo_two";
    char buffer[256];
    char response[] = "Hello Client. How are you?";
    int fd1, fd2;

    // Read message from FIFO1 sent by client
    fd1 = open(FIFO1, O_RDONLY);
    read(fd1, buffer, sizeof(buffer));
    printf("From client: %s\n", buffer);
    close(fd1);

    // Write a response to FIFO2 for client
    fd2 = open(FIFO2, O_WRONLY);
    write(fd2, response, sizeof(response));
    close(fd2);

    // cleaning fifos after work done
    unlink(FIFO1);
    unlink(FIFO2);

    return 0;
}


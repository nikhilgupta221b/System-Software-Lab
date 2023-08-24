#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd;
    int mode;

    // Open the file for reading and writing
    fd = open("file.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);

    // Get the file access mode using fcntl
    mode = fcntl(fd, F_GETFL);

    // Check the access mode and print the result
    if (mode & O_RDWR) {
        printf("Read and Write\n");
    } else if (mode & O_RDONLY) {
        printf("Read Only\n");
    } else if (mode & O_WRONLY) {
        printf("Write Only\n");
    } else {
        printf("Mode not known.\n");
    }

    close(fd);

    return 0;
}


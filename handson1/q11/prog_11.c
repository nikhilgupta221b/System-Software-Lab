#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main() {

    int fd, fd_dup, fd_dup2, fd_fcntl;
    char inputData[] = "ABCDEFG\n";

    // Open the file for writing and writing using original file descriptor
    fd = open("file.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    write(fd, inputData, sizeof(inputData) - 1);
    
    // Duplicate the file descriptor using dup and writing
    fd_dup = dup(fd);
    write(fd_dup, inputData, sizeof(inputData) - 1);
    
    // Duplicate the file descriptor using dup2 and writing
    fd_dup2 = dup2(fd, 15); // Using 10 as the new descriptor
    write(fd_dup2, inputData, sizeof(inputData) - 1);
    
    // Duplicate the file descriptor using fcntl
    fd_fcntl = fcntl(fd, F_DUPFD, 0); // Using the next available descriptor
    write(fd_fcntl, inputData, sizeof(inputData) - 1);
    

    close(fd);
    close(fd_dup);
    close(fd_dup2);
    close(fd_fcntl);

    return 0;
}


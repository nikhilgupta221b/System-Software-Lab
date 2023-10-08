#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int main() {
    char buff[80];
    int fd[2],p;
    p = pipe(fd);
    if(p == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    if (fork()) {
        close(fd[0]); 
        printf("Enter message to the child: ");
        scanf(" %[^\n]", buff); 
        write(fd[1], buff, sizeof(buff));
    }
    else {
        close(fd[1]); 
        read(fd[0], buff, sizeof(buff));
        printf("Message from parent: %s\n", buff);
    }
    wait(0); 
    return 0;
}

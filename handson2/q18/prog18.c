#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int fd1[2], fd2[2];

    // Create the first pipe for "ls -l | grep ^d"
    if (pipe(fd1) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Create the second pipe for "grep ^d | wc -l"
    if (pipe(fd2) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Child process for "ls -l"
    if (fork() == 0) {
        dup2(fd1[1], STDOUT_FILENO);
        close(fd1[0]);
        close(fd1[1]);
        close(fd2[0]);
        close(fd2[1]);
        execlp("ls", "ls", "-l", NULL);
        perror("execlp");
        exit(EXIT_FAILURE);
    }

    // Child process for "grep ^d"
    if (fork() == 0) {
        dup2(fd1[0], STDIN_FILENO);
        dup2(fd2[1], STDOUT_FILENO);
        close(fd1[0]);
        close(fd1[1]);
        close(fd2[0]);
        close(fd2[1]);
        execlp("grep", "grep", "^d", NULL);
        perror("execlp");
        exit(EXIT_FAILURE);
    }

    // Child process for "wc -l"
    if (fork() == 0) {
        dup2(fd2[0], STDIN_FILENO);
        close(fd1[0]);
        close(fd1[1]);
        close(fd2[0]);
        close(fd2[1]);
        execlp("wc", "wc", NULL, NULL);
        perror("execlp");
        exit(EXIT_FAILURE);
    }

    // Parent closes all ends of the pipes and waits for child processes
    close(fd1[0]);
    close(fd1[1]);
    close(fd2[0]);
    close(fd2[1]);
    wait(NULL);
    wait(NULL);
    wait(NULL);

    return 0;
}


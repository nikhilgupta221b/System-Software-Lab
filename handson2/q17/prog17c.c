#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main() {
    int fd[2];

    // Create a pipe
    if (pipe(fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Create child process for 'ls'
    if (fork() == 0) {
        // Close the read end
        close(fd[0]);

        // Close standard output and use fcntl to duplicate the write end of the pipe
        close(STDOUT_FILENO);
        if (fcntl(fd[1], F_DUPFD, STDOUT_FILENO) == -1) {
            perror("fcntl");
            exit(EXIT_FAILURE);
        }
        close(fd[1]);

        // Execute 'ls -l'
        execlp("ls", "ls", "-l", NULL);
        
        // If execlp fails
        perror("execlp");
        exit(EXIT_FAILURE);
    }

    // Create child process for 'wc'
    if (fork() == 0) {
        // Close the write end
        close(fd[1]);

        // Close standard input and use fcntl to duplicate the read end of the pipe
        close(STDIN_FILENO);
        if (fcntl(fd[0], F_DUPFD, STDIN_FILENO) == -1) {
            perror("fcntl");
            exit(EXIT_FAILURE);
        }
        close(fd[0]);

        // Execute 'wc'
        execlp("wc", "wc", NULL);
        
        // If execlp fails
        perror("execlp");
        exit(EXIT_FAILURE);
    }

    // Parent closes both ends of the pipe and waits for both child processes
    close(fd[0]);
    close(fd[1]);
    wait(NULL);
    wait(NULL);

    return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
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
        // Child process redirects its output to the pipe
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);
        
        // Execute 'ls -l'
        execlp("ls", "ls", "-l", NULL);
        
        // If execlp fails
        perror("execlp");
        exit(EXIT_FAILURE);
    }

    // Create child process for 'wc'
    if (fork() == 0) {
        // Child process redirects its input to the pipe
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);
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


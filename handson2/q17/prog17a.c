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
        close(fd[0]);       // Close the read end
        close(STDOUT_FILENO); // Close standard output
        dup(fd[1]);         // The next available fd (STDOUT_FILENO) will be used
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
        close(fd[1]);       // Close the write end
        close(STDIN_FILENO);  // Close standard input
        dup(fd[0]);         // The next available fd (STDIN_FILENO) will be used
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


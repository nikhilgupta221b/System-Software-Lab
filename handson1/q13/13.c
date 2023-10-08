/*
============================================================================
Name : 13.c
Author : Nikhil Gupta
Description : Write a c program so that we wait for 10 secs to get input from std input
Date: 24th Aug, 2023.
============================================================================
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    fd_set read_fds;
    FD_ZERO(&read_fds); // Initialize the file descriptor set
    FD_SET(STDIN_FILENO, &read_fds); // Add stdin to the set
    
    
    struct timeval waitTime;
    waitTime.tv_sec = 10; // Set the timeout to 10 seconds
    waitTime.tv_usec = 0;

    printf("Waiting for input from stdin for 10 seconds...\n");

    int detect = select(STDIN_FILENO + 1, &read_fds, NULL, NULL, &waitTime);

    if (detect == -1) {
        perror("Error :");
        return 1;
    } 
    
    if (detect == 0) {
        printf("No input received within 10 seconds.\n");
    } else {
        if (FD_ISSET(STDIN_FILENO, &read_fds)) {
            printf("Input is available within 10 seconds!\n");
        }
    }

    return 0;
}


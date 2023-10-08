/*
============================================================================
Name : 15.c
Author : Nikhil Gupta
Description : Write a c program to print environment variables
Date: 24th Aug, 2023.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>

// External variable that stores the environment variables
extern char **environ;

int main() {
    char **env = environ;

    printf("Environmental Variables:\n");

    while (*env) {
        printf("%s\n", *env);
        env++;
    }

    return 0;
}


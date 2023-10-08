/*
============================================================================
Name : 14.c
Author : Nikhil Gupta
Description : Write a c program to print the type of a file
Date: 24th Aug, 2023.
============================================================================
*/




#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    printf("Enter Choice:\n");
    printf("1. stat\n");
    printf("2. lstat\n");
    printf("3. fstat\n");

    int choice;
    scanf("%d", &choice);

    struct stat st, lst, fst;

    if (choice == 1) {
        stat("file.txt", &st);
    } else if (choice == 2) {
        lstat("file.txt", &lst);
    } else if (choice == 3) {
        int fd = open("file.txt", O_RDONLY);
        if (fd == -1) {
            perror("Error opening file");
            return 1;
        }
        if (fstat(fd, &fst) == -1) {
            perror("Error in fstat");
            close(fd);
            return 1;
        }
        close(fd);
    } else {
        printf("NOT A VALID CHOICE\n");
        return 1;
    }

    if (S_ISREG(st.st_mode)) {
        printf("Regular File\n");
    } else if (S_ISDIR(st.st_mode)) {
        printf("Directory File\n");
    } else if (S_ISBLK(st.st_mode)) {
        printf("Block File\n");
    } else if (S_ISCHR(st.st_mode)) {
        printf("Character File\n");
    } else if (S_ISLNK(st.st_mode)) {
        printf("Symbolic Link\n");
    } else if (S_ISSOCK(st.st_mode)) {
        printf("Socket\n");
    } else if (S_ISFIFO(st.st_mode)) {
        printf("Fifo File\n");
    } else {
        printf("Unknown\n");
    }

    return 0;
}


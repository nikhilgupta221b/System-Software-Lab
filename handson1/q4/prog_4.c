/*
============================================================================
Name : 4.c
Author : Nikhil Gupta
Description : Write a c program to open a file
Date: 24th Aug, 2023.
============================================================================
*/



#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include<errno.h>

int main(){
	// Opening file without checking lock
	int fd = open("tempfile.txt", O_RDWR);
	if (fd == -1) {
		perror("Error in opening file: ");
	}
	else {
		printf("File is opened successfully in Read Write mode.\n");
	}
	close(fd);
	return 0;
}

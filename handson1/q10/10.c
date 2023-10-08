/*
============================================================================
Name : 10.c
Author : Nikhil Gupta
Description : Write a c program to input into a file and use lseek
Date: 24th Aug, 2023.
============================================================================
*/



#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(){
	
	int fd;
	
	char firstData[] = "abcdefghij";
	char secondData[] = "pqrstuvwxy";
	
	// Open file in read-write mode and create if doesn't exist
	fd = open("file.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
	
	// Writing first 10 bytes of data
	write(fd, firstData, sizeof(firstData) - 1);
	
	// Move the file pointer by 10 bytes
	lseek(fd, 10, SEEK_CUR);
	
	// Current Offset
	int pointerPosition = lseek(fd, 0, SEEK_CUR);
    	printf("Current value of file pointer is: %d\n", pointerPosition);
	
	// Write second 10 bytes of data
	write(fd, secondData, sizeof(secondData) -1);
	
	close(fd);
	
	printf("Data Written Successfully.\n");

	return 0;
}

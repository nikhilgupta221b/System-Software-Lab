/*
============================================================================
Name : 3.c
Author : Nikhil Gupta
Description : Write a c program to create new files and print file descriptor value
Date: 24th Aug, 2023.
============================================================================
*/
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>

int main() {
	int fd1 = creat("temp1.txt", 0644);
	int fd2 = creat("temp2.txt", 0644);
	if (fd1 == -1 || fd2 == -1)
	{
		perror("Error in creating file");
	}
	else {
		printf("Files created successfully.\nFD1 = %d\nFD2 = %d", fd1, fd2);
	}
	close(fd1);
	close(fd2);
	return 0;
}

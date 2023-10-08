/*
============================================================================
Name : 22.c
Author : Nikhil Gupta
Description : Write a c program to create a child process and update a file
Date: Sept 1, 2023.
============================================================================
*/
#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/wait.h>

int main() {
	int fd;
	fd = open("file.txt", O_RDWR);
	if(!fork()){
		write(fd, "Hello", 5);
	}
	else {
		wait(0);
		write(fd, "World", 5);
	}	

	close(fd);
	return 0;
}

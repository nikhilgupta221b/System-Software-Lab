/*
============================================================================
Name : 6.c
Author : Nikhil Gupta
Description : Write a c program to read input from std input and show output on std output
Date: 24th Aug, 2023.
============================================================================
*/



#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(){

	char buffer[64];
	ssize_t noOfBytes;

	while ((noOfBytes = read(STDIN_FILENO, buffer, sizeof(buffer))) > 0) {
		write(STDOUT_FILENO, buffer, noOfBytes);
		printf("\n");
	}

	if (noOfBytes == -1) {
		perror("Error : ");
	}

	return 0;
}

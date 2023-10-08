/*
============================================================================
Name : 27d.c
Author : Nikhil Gupta
Description : Write a c program to implement execlp
Date: Sept 8, 2023.
============================================================================*/
#include<stdio.h>
#include<unistd.h>

int main(){
	if (execlp("ls", "ls", "-Rl", (char *) NULL) == -1){
		perror("Error: ");
		return 1;
	}
	return 0;
}

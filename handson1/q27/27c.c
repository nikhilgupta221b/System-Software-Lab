/*
============================================================================
Name : 27c.c
Author : Nikhil Gupta
Description : Write a c program to implement execle
Date: Sept 8, 2023.
============================================================================*/
#include<stdio.h>
#include<unistd.h>
int main(){
	char *envp[] = {
	"PATH=/bin:/usr/bin",
	NULL
	};

	if (execle("/bin/ls", "ls", "-Rl", (char *) NULL, envp) == -1) {
		perror("Error: ");
		return 1;
	}
	return 0;
}	

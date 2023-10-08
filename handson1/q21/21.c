/*
============================================================================
Name : 21.c
Author : Nikhil Gupta
Description : Write a c program to implement fork()
Date: Sept 1, 2023.
============================================================================
*/
#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>


int main() {
	if (!fork()){
		printf("Child Process ID: %d\n", getpid());
		printf("Parent Process ID: %d\n", getppid());
	}
	else {
		wait(0);
	}
	return 0;
}

/*
============================================================================
Name : 24.c
Author : Nikhil Gupta
Description : Write a c program to implement orphan process
Date: Sept 1, 2023.
============================================================================*/
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
int main(){
	if (!fork()){
		printf("Child is executing PID : %d\n", getpid());
		sleep(30);
	}
	else {
		printf("Parent exited.\n");
		sleep(2);
		exit(0);
	}
	return 0;
}

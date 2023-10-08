/*
============================================================================
Name : 23.c
Author : Nikhil Gupta
Description : Write a c program to implement zombie process
Date: Sept 1, 2023.
============================================================================*/
#include<stdio.h>
#include<unistd.h>

int main(){
	if (!fork()){
		printf("Chile executed and terminated\n");
		printf("Child Process ID: %d", getpid());
	}
	else {
		printf("Parent busy with other task\n");
		for (;;); 
	}
	return 0;
}

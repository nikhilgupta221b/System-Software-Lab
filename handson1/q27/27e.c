/*
============================================================================
Name : 27e.c
Author : Nikhil Gupta
Description : Write a c program to implement execvp
Date: Sept 8, 2023.
============================================================================*/
#include<stdio.h>
#include<unistd.h>
int main(){
	char *args[] = {"ls", "-Rl", NULL};
	if (execvp("ls", args) == -1){
		perror("Error: ");
		return 1;
	}
	return 0;
}

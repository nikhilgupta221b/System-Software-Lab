/*
============================================================================
Name : 27a.c
Author : Nikhil Gupta
Description : Write a c program to implement execl
Date: Sept 8, 2023.
============================================================================*/
#include<stdio.h>
#include<unistd.h>
int main(){
	if (execl("/bin/ls", "ls", "-Rl", (char *)NULL) == -1){
		perror("Error: ");
		return 1;
	}
	return 0;
}

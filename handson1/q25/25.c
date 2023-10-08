/*
============================================================================
Name : 25.c
Author : Nikhil Gupta
Description : Write a c program to implement waitpid()
Date: Sept 8, 2023.
============================================================================*/
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>

int main(){
	int child1_id = fork();
	if (!child1_id){
		printf("Child 1 PID: %d\n", getpid());
		sleep(1);
	}
	else {
		int child2_id = fork();
		if (!child2_id){
			printf("Child 2 PID: %d\n", getpid());
			sleep(1);
		}
		else {
			int child3_id = fork();
			if (!child3_id){
				printf("Child 3 PID: %d\n", getpid());
				sleep(1);
			}
			else {
				int status;
				pid_t terminated_pid;
				printf("Parent is waiting for child 2.\n");
				terminated_pid = waitpid(child2_id, &status, 0);
				printf("Parent exited after child with id : %d is completed.\n", terminated_pid);
			}
		}

	}

	return 0;
}

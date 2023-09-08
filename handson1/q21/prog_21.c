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

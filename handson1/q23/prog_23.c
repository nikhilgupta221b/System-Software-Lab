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

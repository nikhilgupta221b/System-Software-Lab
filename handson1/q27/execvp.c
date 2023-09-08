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

#include<stdio.h>
#include<unistd.h>

int main(){
	if (execlp("ls", "ls", "-Rl", (char *) NULL) == -1){
		perror("Error: ");
		return 1;
	}
	return 0;
}

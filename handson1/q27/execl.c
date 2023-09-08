#include<stdio.h>
#include<unistd.h>
int main(){
	if (execl("/bin/ls", "ls", "-Rl", (char *)NULL) == -1){
		perror("Error: ");
		return 1;
	}
	return 0;
}

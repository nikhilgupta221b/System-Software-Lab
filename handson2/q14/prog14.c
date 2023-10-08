#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(){
	int i, size, fd[2];
	char buf[20];
	i = pipe(fd);
	if (i == -1){
		perror("Not created");
		exit(EXIT_FAILURE);
	}
	char message[] = "Hello\n";
	size = write(fd[1], message, sizeof(message));
	read(fd[0], buf, size);
	printf("Reading from pipe: %s\n", buf);
	return 0;
}

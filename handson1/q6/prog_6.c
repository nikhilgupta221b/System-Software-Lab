#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(){

	char buffer[64];
	ssize_t noOfBytes;

	while ((noOfBytes = read(STDIN_FILENO, buffer, sizeof(buffer))) > 0) {
		write(STDOUT_FILENO, buffer, noOfBytes);
		printf("\n");
	}

	if (noOfBytes == -1) {
		perror("Error : ");
	}

	return 0;
}

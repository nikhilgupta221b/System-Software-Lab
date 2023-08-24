#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include<errno.h>

int main(){
	int fd_excl = open("tempfile.txt", O_RDWR | O_EXCL);

	if (fd_excl == -1) {
		perror("Error in opening file: ");
	}
	else {
		printf("File is opened successfully in Read Write mode with EXCL flag.\n");
	}

	close(fd_excl);
	return 0;
}

#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/wait.h>

int main() {
	int fd;
	fd = open("file.txt", O_RDWR);
	if(!fork()){
		write(fd, "Hello", 5);
	}
	else {
		wait(0);
		write(fd, "World", 5);
	}	

	close(fd);
	return 0;
}

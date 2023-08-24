#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>


int main(){
	
	int fd1 = creat("file1.txt", 0744);
	if (fd1 == -1) {
		perror("Error: ");
	}
	else {
		printf("File 1 created with FD1 = %d\n", fd1);
	}
	sleep(10);
	
	
	int fd2 = creat("file2.txt", 0744);
	if (fd2 == -1) {
		perror("Error: ");
	}
	else {
		printf("File 2 created with FD2 = %d\n", fd1);
	}
	sleep(10);
	
	
	int fd3 = creat("file3.txt", 0744);
	if (fd3 == -1) {
		perror("Error: ");
	}
	else {
		printf("File 3 created with FD3 = %d\n", fd1);
	}
	sleep(10);
	
	
	int fd4 = creat("file4.txt", 0744);
	if (fd4 == -1) {
		perror("Error: ");
	}
	else {
		printf("File 4 created with FD4 = %d\n", fd1);
	}
	sleep(10);
	
	
	int fd5 = creat("file5.txt", 0744);
	if (fd5 == -1) {
		perror("Error: ");
	}
	else {
		printf("File 5 created with FD5 = %d\n", fd1);
	}
	
	close(fd1);
	close(fd2);
	close(fd3);
	close(fd4);
	close(fd5);
		
	return 0;
}

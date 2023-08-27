#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/file.h>

int main(){

	struct flock lock;
	int fd;

	fd = open("file.txt", O_RDWR);

	lock.l_type = F_WRLCK;
	lock.l_whence = SEEK_SET;
	lock.l_start = 0; // l_start and l_len are 0 for mandatory locking
	lock.l_len = 0;
	lock.l_pid = getpid();

	printf("Waiting for lock\n");
	fcntl(fd, F_SETLKW, &lock);
	printf("Inside Critical Section\n");
	printf("Press Enter to release the lock\n");
	getchar();

	printf("Lock is released.\n");

	lock.l_type = F_UNLCK;
	fcntl(fd, F_SETLK, &lock);

	return 0;
}


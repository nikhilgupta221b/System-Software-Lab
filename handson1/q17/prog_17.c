#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/file.h>


int main() {

	struct{
	int ticket;
	} db;
	
	struct flock lock;
	lock.l_type = F_WRLCK;
	lock.l_whence = SEEK_SET;
	lock.l_start = 0;
	lock.l_len = 0;
	lock.l_pid = getpid();
	
	int fd;
	fd = open("db", O_RDWR);
	
	printf("Waiting for lock\n");
	fcntl(fd, F_SETLKW, &lock);
	printf("Inside Critical Section\n");
	
	//Read current db value
	read(fd, &db, sizeof(db));
	printf("Old value :  %d\n", db.ticket);
	db.ticket++;
	printf("New Value : %d\n", db.ticket);
		
	// move pointer to beginning and write new value in db
	lseek(fd, 0, SEEK_SET);
	write(fd, &db, sizeof(db));
	
	printf("Press Enter to exit\n");
	getchar();
	
	lock.l_type = F_UNLCK;
	fcntl(fd, F_SETLK, &lock);
	
	return 0;
	
}
	
	
	
	

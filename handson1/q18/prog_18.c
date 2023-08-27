#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/file.h>


struct Train{
		int train_no;
		int ticket_no;
	};
	

int main(){

	int fd, num;
	struct Train train;
	fd = open("db.txt", O_RDWR);
	
	printf("Select a train number: 1, 2 or 3:\n");
	scanf("%d", &num);
	num--; // Array index is one less
	
	// Intializing lock
	struct flock lock;
	lock.l_type = F_WRLCK;
	lock.l_whence = SEEK_SET;
	lock.l_start = num * sizeof(train);
	lock.l_len = sizeof(train);
	lock.l_pid = getpid();
	
	// Apply Write Lock
	printf("Waiting for lock\n");
	fcntl(fd, F_SETLKW, &lock);
	printf("Lock Acquired.\n");
	
	//Reading value of train data and updating it.
	lseek(fd, num * sizeof(train), SEEK_SET);
	read(fd, &train, sizeof(train));
	printf("Current Ticket number :%d\n", train.ticket_no);
	train.ticket_no++;
	
	// Moving pointer back to beginning of this record
	lseek(fd, num * sizeof(train), SEEK_SET);
	printf("Press Enter to book ticket\n");
	getchar();
	getchar();
	write(fd, &train, sizeof(train));
	
	// Unlock
	lock.l_type = F_UNLCK;
	fcntl(fd, F_SETLK, &lock);
	
	
	printf("Ticket booked with number : %d\n", train.ticket_no);
	
	close(fd);
	
	return 0;
	
}
	

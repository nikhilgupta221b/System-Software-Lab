#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>


struct Train {
		int train_no;
		int ticket_no;
	};
int main() {
	int i, fd;
	struct Train db[3];
	
	for (int i = 0; i < 3; i++) {
		db[i].train_no = i+1;
		db[i].ticket_no = 0;
	}
	
	fd = open("db.txt", O_RDWR | O_CREAT, 0644);
	write (fd, db, sizeof(db));

	close(fd);
	
	return 0;
}

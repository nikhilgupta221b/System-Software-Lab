/*
============================================================================
Name : 17a.c
Author : Nikhil Gupta
Description : Write a c program to create ticket database
Date: 27th Aug, 2023.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>



int main(){
	int fd;
	struct {
		int ticket;
	} db;

	db.ticket = 10;
	
	fd = open ("db", O_RDWR | O_CREAT, 0644);
	write(fd, &db, sizeof(db));
	close(fd);
	fd = open ("db", O_RDONLY);
	read(fd, &db, sizeof(db));
	printf("Ticket no : %d\n", db.ticket);
	close(fd);
	
	return 0;
	
}

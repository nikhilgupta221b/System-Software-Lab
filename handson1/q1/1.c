/*
============================================================================
Name : 1.c
Author : Nikhil Gupta
Description : Wrtie a c program to create link files
Date: 23rd Aug, 2023.
============================================================================
*/
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

int main()
{
	// Creating Soft Link
	if (symlink("temp_c","temp_c_sl") == 0) {
		printf("Softlink created successfully\n");
	}
	else {
		perror("Error creating Softlink");
	}

	// Creating Hard Link
	if (link("temp_c","temp_c_hl") == 0) {
		printf("Hardlink created successfully\n");
	}
	else {
		perror("Error creating Hardlink");
	}

	// Creating FIFO
	if (mknod("temp_c_FIFO", S_IFIFO, 0)==0) {
		printf("FIFO created successfully\n");
	}
	else {
		perror("Error creating FIFO");
	}


	return 0;

}

/*
============================================================================
Name : 9.c
Author : Nikhil Gupta
Description : Write a c program to print details of a file
Date: 24th Aug, 2023.
============================================================================
*/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>

int main(){

	struct stat fileStat;
	int fd;
	
	fd = open("file.txt", O_RDONLY);
	
	fstat(fd, &fileStat);
	
	printf("Inode Number: %lu\n",fileStat.st_ino);
	
	printf("Number of Hard Links: %lu\n",fileStat.st_nlink);
	
	printf("uid: %d\n",fileStat.st_uid);

	printf("gid: %d\n",fileStat.st_gid);
	
	printf("Size: %lu bytes\n",fileStat.st_size);
	
	printf("Block Size: %lu\n", fileStat.st_blksize);
	
	printf("Number of Blocks: %lu\n", fileStat.st_blocks);
	
	printf("Time of Last Access: %lu\n", fileStat.st_atim.tv_nsec);
	
	printf("TIme of Last Modification: %lu\n", fileStat.st_mtim.tv_nsec);
	
	printf("Time of Last Change: %lu\n", fileStat.st_ctim.tv_nsec);
	
	return 0;
}

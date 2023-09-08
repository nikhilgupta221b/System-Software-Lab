#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<time.h>

int main(){
	if (!fork()){
		// inside child
		// making child a daemon process
		setsid();
		chdir("/");
		umask(0);

		// our job logic
		while (1){
			time_t t;
			struct tm *tm_info;
			time(&t);
			tm_info = localtime(&t);

			if (tm_info->tm_hour == 14 && tm_info->tm_min == 30) {
				system("/home/nikhil/sslab/handson1/q30/hello_world");
				sleep(60);
			}
			sleep(30);
		}
		

		return 0;
	}
	else{
		exit(0);
	}
	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
	char buf1[200], buf2[200];
	int fd1[2], p1, fd2[2], p2;
	p1 = pipe(fd1);
	if (p1 == -1){
		perror("Failed Pipe1");
		exit(EXIT_FAILURE);
	}
	p2 = pipe(fd2);
	if (p2 == -1){
		perror("pipe2");
        	exit(EXIT_FAILURE);
    	}
    	// child
    	if (!fork()){
    		close(fd1[0]); // close read end of fd1 for child
    		close(fd2[1]); // close write end of fd2 for child
    		printf("Enter message to parent: ");
    		scanf("%[^\n]", buf1);
    		write (fd1[1], buf1, sizeof(buf1));
    		read(fd2[0], buf2, sizeof(buf2));
    		printf("Message from parent: %s\n", buf2);
    	}
    	else {
    		close(fd1[1]); // close write end of fd1 for parent
    		close(fd2[0]); // close read end of fd2 for parent
    		// child first wrote into fd1 so read from fd1 first
    		read(fd1[0], buf1, sizeof(buf1));
    		printf("Message from child: %s\n", buf1);
    		printf("Enter message to child: ");
    		scanf("%[^\n]", buf2);
    		write(fd2[1], buf2, sizeof(buf2));
    	}
    	wait(0);
    	return 0;
}

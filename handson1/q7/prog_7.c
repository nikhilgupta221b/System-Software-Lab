#include<unistd.h>
#include<fcntl.h>
int main(){
	int fd1, fd2, bytesRead;
	char buffer[64];
	
	// Open file 1
	fd1 = open("file1.txt", O_RDONLY);
	
	// Create file2 if it doesn't exist otherwise delete it's content if it exist
	fd2 = open("file2.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	
	// Read from file1 into buffer and write to file2
	while ((bytesRead = read(fd1, buffer, sizeof(buffer))) > 0){
		write(fd2,buffer,bytesRead);
	}
	
	close(fd1);
	close(fd2);
	
	return 0;
}

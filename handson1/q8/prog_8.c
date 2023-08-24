#include<unistd.h>
#include<fcntl.h>
int main(){
	int fd;
	
	
	char buffer[1]; // Reading one character at a time.
	ssize_t noBytes;
	
	
	fd = open("file1.txt", O_RDONLY);
	
	while ((noBytes = read(fd, buffer, sizeof(buffer))) > 0) {
	// If the read character is a newline character write "\n"(newline) on screen.
        if (buffer[0] == '\n') {
            write(STDOUT_FILENO, "\n", 1);
        }
        // Otherwise write the character that is read from the file. 
        else {
            write(STDOUT_FILENO, buffer, 1);
        }
    }
	return 0;
}

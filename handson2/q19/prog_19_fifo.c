#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main() {
    int result = mkfifo("myfifo", 0666);
    if (result == -1) {
        perror("mkfifo");
        return 1;
    }
    printf("FIFO 'myfifo' created.\n");
    return 0;
}

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main() {
    int result = mknod("myfifo_nod", S_IFIFO | 0666, 0);
    if (result == -1) {
        perror("mknod");
        return 1;
    }
    printf("FIFO 'myfifo_nod' created.\n");
    return 0;
}

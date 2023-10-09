#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/resource.h>
#include <limits.h>

int main() {
    struct rlimit rlim;
    int max_files;
    long pipe_size;

    if (getrlimit(RLIMIT_NOFILE, &rlim) == 0) {
        if (rlim.rlim_max == RLIM_INFINITY) {
            printf("Maximum number of files that can be opened: unlimited\n");
        } else {
            max_files = rlim.rlim_max;
            printf("Maximum number of files that can be opened: %d\n", max_files);
        }
    } else {
        perror("getrlimit");
        exit(EXIT_FAILURE);
    }

    pipe_size = (long)PIPE_BUF; // PIPE_BUF is the minimum guaranteed size
    printf("Size of a pipe (circular buffer): %ld bytes\n", pipe_size);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <fcntl.h> 

int main() {

    int key, shm_id;
    char *shared_memory;
    
    // creating key    
    key = ftok(".", 'b');
    
    // creating shared memory of 10 bytes
    shm_id = shmget(key, 10, IPC_CREAT | 0744);
    if (shm_id == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }
    
    // attaching shared memory to process
    shared_memory = shmat(shm_id, 0, 0);
    if (shared_memory == (char *)-1) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }
    
    printf("Enter text (10 chars): ");
    // reading 9 characters to shared memory
    scanf("%9s", shared_memory); 
    printf("Data read from shared memory: %s\n", shared_memory);

    // Get the ID of the shared memory in read-only mode.
    int read_only_shm_id = shmget(key, 10, 0 | SHM_RDONLY);
    if (read_only_shm_id == -1) {
        perror("shmget (read-only)");
        exit(EXIT_FAILURE);
    }

    // Attach the read-only shared memory segment to the address space of the process.
    char *read_only_memory = shmat(read_only_shm_id, 0, 0);
    if (read_only_memory == (char *)-1) {
        perror("shmat (read-only)");
        exit(EXIT_FAILURE);
    }
    
    // Attempt to write to the read-only memory.
    strncpy(read_only_memory, "This should not overwrite!", 10);

    // Detach the original shared memory segment from the process.
    if (shmdt(shared_memory) == -1) {
        perror("shmdt");
        exit(EXIT_FAILURE);
    }
    
    // Detach the read-only shared memory segment from the process.
    if (shmdt(read_only_memory) == -1) {
        perror("shmdt (read-only)");
        exit(EXIT_FAILURE);
    }

    // Mark the shared memory segment for deletion.
    if (shmctl(shm_id, IPC_RMID, NULL) == -1) {
        perror("shmctl (IPC_RMID)");
        exit(EXIT_FAILURE);
    }

    printf("Shared memory detached and removed.\n");

    return 0;
}

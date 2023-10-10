#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int main() {
    int key;
    int semid;

    // generating key
    key = ftok(".", 'a'); 

    if (key == -1) {
        perror("ftok");
        exit(1);
    }
    
    // Create a semaphore set with 2 semaphores
    semid = semget(key, 2, IPC_CREAT | 0666);

    if (semid == -1) {
        perror("semget");
        exit(1);
    }

    // Initialize the first semaphore (index 0) in the set as a binary semaphore with value 1.
    if (semctl(semid, 0, SETVAL, 1) == -1) {
        perror("semctl");
        exit(1);
    }

    // Initialize the second semaphore (index 1) in the set as a counting semaphore with value 5.
    if (semctl(semid, 1, SETVAL, 5) == -1) {
        perror("semctl");
        exit(1);
    }

    printf("Binary semaphore and counting semaphore created and initialized.\n");

    // Remove the entire semaphore set.
    if (semctl(semid, 0, IPC_RMID) == -1) {
        perror("semctl (IPC_RMID)");
    }

    return 0;
}

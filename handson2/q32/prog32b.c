#include <sys/ipc.h>   
#include <sys/sem.h>   
#include <sys/types.h> 
#include <sys/shm.h>   
#include <unistd.h>    
#include <stdio.h>  

void main(){

    // Union needed for setting the semaphore value
    union semun{
        int val;               // Value of the semaphore
        struct semid_ds *buf;  /* Buffer for IPC_STAT, IPC_SET */
        unsigned short *array; /* Array for GETALL, SETALL */
        struct seminfo *__buf; /* Buffer for IPC_INFO */
    } semvar;

    // Generate a key for the semaphore using the current directory and character 'e'
    int key=ftok(".",'e');
    if(key==-1){
      perror("ftok returns");
      return;
    }

    // Try to get an existing semaphore ID with the given key
    int semid= semget(key,1,0);
    if(semid==-1){
        // If the semaphore doesn't exist, create one with permissions 0700
        semid = semget(key,1,IPC_CREAT|0700);
        if(semid==-1){
          perror("semget returns");
          return;
        }

        // Set the initial value of the semaphore to 1 (binary semaphore)
        semvar.val = 1; 
        int semctlflag = semctl(semid,0,SETVAL,semvar);
        if(semctlflag==-1){
          perror("semctl returns");
          return;
        }
    }

    // Generate a key for the shared memory using the current directory and character 'f'
    int shmkey = ftok(".",'f');
    if(shmkey==-1){
      perror("shm ftok returns");
      return;
    }

    // Create or get shared memory of 20 bytes with permissions 0700
    int shmid= shmget(shmkey,20,IPC_CREAT|0700); 
    if(shmid==-1){
      perror("shmget returns");
      return;
    }

    // Attach the shared memory segment to the address space of the calling process
    char *shmpointer= shmat(shmid,(void *)0,0);
    if(*shmpointer==-1){
      perror("Error while attaching address space!");
      return;
    }

    struct sembuf semOp;
    semOp.sem_num = 0;
    semOp.sem_flg = 0;

    printf("Press enter to lock the critical section!\n");
    getchar();

    // Decrease the semaphore's value by 1 to acquire a lock
    semOp.sem_op = -1;
    int semopflag = semop(semid,&semOp,1);
    if(semopflag==-1){
      perror("semop returns");
      return;
    }

    // Start of the critical section
    printf("Critical Section is now locked!\n");

    // Write a string to the shared memory
    printf("Writing to the shared memory!\n");
    sprintf(shmpointer, "Hello Nikhil! Welcome.");

    printf("Press enter to read from the shared memory!\n");
    getchar();
    // Read and print the string from shared memory
    printf("%s\n", shmpointer);

    printf("Press enter to exit the critical section!\n");
    getchar();

    // Increase the semaphore's value by 1 to release the lock
    semOp.sem_op = 1;
    semopflag = semop(semid,&semOp,1);
    if(semopflag==-1){
      perror("Error while operating on semaphore!");
      return;
    }

    printf("Critical section is now unlocked!\n");
}


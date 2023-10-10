#include<sys/ipc.h>   
#include<sys/sem.h>   
#include<sys/types.h> 
#include<fcntl.h>     
#include<unistd.h>    
#include<stdio.h>     

void main(){
    char *ticketFile = "ticket_file.txt";             
    int lseekOffset;
    int data;
    
    // Union needed for setting the semaphore value
    union semun{
        int val;               // Value of the semaphore
        struct semid_ds *buf;  /* Buffer for IPC_STAT, IPC_SET */
        unsigned short *array; /* Array for GETALL, SETALL */
        struct seminfo *__buf; /* Buffer for IPC_INFO */
    } semvar;

    // Open (or create) the ticket file with read-write permissions
    int fd = open(ticketFile,O_CREAT|O_RDWR,S_IRWXU);
    if(fd==-1){
      perror("fd returns");
      return ;
    }

    // Generate a key for the semaphore
    int key = ftok(".",'d');
    if(key==-1){
      perror("sempahore key returns");
      return;
    }
    
     // Try to get an existing semaphore ID with the given key
    int semid = semget(key,1,0);
    if(semid==-1){
        // If the semaphore doesn't exist, create one with permissions 0700
        semid = semget(key,1,IPC_CREAT|0700); 
        if(semid==-1){
          perror("semid returns");
          return;
        }
        // Set the initial value of the semaphore to 1 (binary semaphore)
        semvar.val = 1; // Set a binary semaphore
        int semctlflag = semctl(semid,0,SETVAL,semvar);
        if(semctlflag==-1){
          perror("semctl returns");
          return;
        }
    }

    struct sembuf semOp; 
    semOp.sem_num = 0;
    semOp.sem_flg = 0;

    printf("Press enter to obtain lock on the critical section\n");
    getchar();
    
    // Decrease the semaphore's value by 1 to acquire a lock
    semOp.sem_op = -1;
    int semopflag = semop(semid,&semOp,1);
    if(semopflag==-1){
      perror("semop returns");
      return;
    }
    
    printf("Obtained lock on critical section!\n");
    printf("Now entering critical section!\n");

    // Read the last ticket number from the file
    int read_bytes = read(fd,&data,sizeof(data));
    if(read_bytes==-1){
      perror("read returns");
      return;
    }
    else if(read_bytes==0) // If the file is empty, start ticket numbers from 1
      data = 1;
    else{
      // Increment the ticket number
      data += 1;
      lseekOffset = lseek(fd,0,SEEK_SET);
      if(lseekOffset==-1){
        perror("lseek returns");
        return;
      }
    }
    // Write the new ticket number to the file
    int write_bytes = write(fd,&data,sizeof(data));
    if(write_bytes==-1){
      perror("write returns");
      return;
    }
    // Display the ticket number to the user
    printf("Your ticker number is - %d\n", data);
    printf("Press enter to exit from critical section!\n");
    getchar();
    
    // Increase the semaphore's value by 1 to release the lock
    semOp.sem_op = 1;
    semopflag = semop(semid,&semOp,1);
    if(semopflag==-1){
      perror("semop returns");
      return;
    }
    
    // Close the ticket file
    close(fd);
}

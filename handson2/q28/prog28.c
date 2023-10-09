#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>


int main() {
    int key;
    int msqid;

    // creating key
    key = ftok(".", 'a'); 

    if (key == -1) {
        perror("ftok");
        exit(1);
    }

    // creating message queue
    msqid = msgget(key, IPC_CREAT|0744);

    if (msqid == -1) {
        perror("msgget");
        exit(1);
    }

    struct msqid_ds info;

    // checking current message queue permissions
    if (msgctl(msqid, IPC_STAT, &info) == -1) {
        perror("msgctl");
        exit(1);
    }
    printf("Access Permission Before: %o\n", info.msg_perm.mode);
    
    // setting new permissions
    info.msg_perm.mode = 0644;  
 
    if (msgctl(msqid, IPC_SET, &info) == -1) {
        perror("msgctl (IPC_SET)");
        exit(1);
    }
    printf("Access Permission After: %o\n", info.msg_perm.mode);
    printf("Message queue permissions updated successfully.\n");

    return 0;

}

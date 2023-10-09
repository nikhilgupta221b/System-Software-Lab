#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main() {
    int key;
    int msqid;

    key = ftok(".", 'a'); 

    if (key == -1) {
        perror("ftok");
        exit(1);
    }

    msqid = msgget(key,  IPC_CREAT|IPC_EXCL|0744);

    if (msqid == -1) {
        perror("msgget");
        exit(1);
    }

    printf("Message queue created successfully.\n");
    printf("Key: %d\n", key);
    printf("Message Queue ID: %d\n", msqid);

    return 0;
}

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

    // removing message queue
    if (msgctl(msqid, IPC_RMID, NULL) == -1) {
        perror("msgctl");
        exit(1);
    }

    printf("Message queue removed successfully.\n");

    return 0;
}

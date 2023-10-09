#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>

// message structure
struct msg_buffer {
    long msg_type;
    char msg_text[100];
};

int main() {
    int key;
    int msqid;
    int receive_flags;
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
    
    struct msg_buffer message;
    
    receive_flags = 0;
    if (msgrcv(msqid, &message, sizeof(message.msg_text), 1, receive_flags) == -1) {
        if (errno == ENOMSG) {
            printf("No message in the queue (IPC_NOWAIT flag used).\n");
        } else {
            perror("msgrcv");
            exit(EXIT_FAILURE);
        }
    } else {
        printf("Received Message (with 0 as flag): %s\n", message.msg_text);
    }
    
    receive_flags = IPC_NOWAIT;
    if (msgrcv(msqid, &message, sizeof(message.msg_text), 1, receive_flags) == -1) {
        if (errno == ENOMSG) {
            printf("No message in the queue (IPC_NOWAIT flag used).\n");
        } else {
            perror("msgrcv");
            exit(EXIT_FAILURE);
        }
    } else {
        printf("Received Message (with IPC_NOWAIT flag): %s\n", message.msg_text);
    }
    msgctl(msqid, IPC_RMID, NULL);
    return 0;
}

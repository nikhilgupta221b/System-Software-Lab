#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>


struct msg_buffer {
    long msg_type;
    char msg_text[100];
};

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

    struct msg_buffer message;
    message.msg_type = 1;
    strcpy(message.msg_text, "Message to Message Queue!");

    if (msgsnd(msqid, &message, sizeof(message.msg_text), 0) == -1) {
        perror("msgsnd");
        exit(EXIT_FAILURE);
    }
    printf("Message sent to the queue: %s\n", message.msg_text);
    return 0;
}

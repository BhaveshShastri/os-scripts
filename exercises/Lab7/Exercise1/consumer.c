#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct msg_buffer {
    long msg_type;
    int number;
} message;

int main() {
    key_t key = ftok("queuefile", 65);
    int msgid = msgget(key, 0666 | IPC_CREAT);

    for (int i = 0; i < 5; i++) {
        msgrcv(msgid, &message, sizeof(message) - sizeof(long), 1, 0);
        printf("Consumed: %d\n", message.number);
    }

    msgctl(msgid, IPC_RMID, NULL); // Remove message queue
    return 0;
}

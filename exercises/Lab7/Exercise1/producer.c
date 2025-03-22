#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

struct msg_buffer {
    long msg_type;
    int number;
} message;

int main() {
    key_t key = ftok("queuefile", 65);
    int msgid = msgget(key, 0666 | IPC_CREAT);

    for (int i = 1; i <= 5; i++) {
        message.msg_type = 1;
        message.number = i * 10;  // Producing multiples of 10
        
        msgsnd(msgid, &message, sizeof(message) - sizeof(long), 0);
        printf("Produced: %d\n", message.number);
        sleep(1); // Simulating production time
    }

    return 0;
}

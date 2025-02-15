#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

int main() {
    key_t key = ftok("shmfile", 65);
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);
    char *str = (char *)shmat(shmid, NULL, 0);

    strcpy(str, "Hello from shared memory writer!");

    printf("Data written in memory: %s\n", str);

    shmdt(str);
    return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <unistd.h>
#include <string.h>

void sem_wait(int semid) {
    struct sembuf sb = {0, -1, 0};
    semop(semid, &sb, 1);
}

void sem_signal(int semid) {
    struct sembuf sb = {0, 1, 0};
    semop(semid, &sb, 1);
}

int main() {
    key_t key = ftok("shmfile", 65);
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);
    char *data = (char *)shmat(shmid, NULL, 0);

    key_t sem_key = ftok("semfile", 65);
    int rw_mutex = semget(sem_key, 1, 0666 | IPC_CREAT);

    while (1) {
        sem_wait(rw_mutex);  // Lock access for writing

        // Writing data
        sprintf(data, "Data written by writer at PID %d", getpid());
        printf("Writer: %s\n", data);
        sleep(2);  // Simulating writing time

        sem_signal(rw_mutex);  // Release lock
        sleep(3);  // Simulate delay before next write
    }

    shmdt(data);
    return 0;
}

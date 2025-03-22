#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <unistd.h>

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

    key_t sem_key1 = ftok("semfile", 65);
    int rw_mutex = semget(sem_key1, 1, 0666 | IPC_CREAT);

    key_t sem_key2 = ftok("countfile", 66);
    int read_count_mutex = semget(sem_key2, 1, 0666 | IPC_CREAT);
    
    int read_count = 0;

    while (1) {
        sem_wait(read_count_mutex);
        read_count++;
        if (read_count == 1) 
            sem_wait(rw_mutex);  // First reader blocks writer
        sem_signal(read_count_mutex);

        // Reading data
        printf("Reader (PID %d) reads: %s\n", getpid(), data);
        sleep(1);  // Simulating reading time

        sem_wait(read_count_mutex);
        read_count--;
        if (read_count == 0) 
            sem_signal(rw_mutex);  // Last reader unblocks writer
        sem_signal(read_count_mutex);

        sleep(2);  // Simulate delay before next read
    }

    shmdt(data);
    return 0;
}

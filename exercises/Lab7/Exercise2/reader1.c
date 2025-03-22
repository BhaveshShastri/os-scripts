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
    if (shmid == -1) {
        perror("shmget failed");
        exit(1);
    }
    char *data = (char *)shmat(shmid, NULL, 0);
    if (data == (char *)-1) {
        perror("shmat failed");
        exit(1);
    }

    key_t sem_key1 = ftok("semfile", 65);
    int rw_mutex = semget(sem_key1, 1, 0666 | IPC_CREAT);
    if (rw_mutex == -1) {
        perror("semget rw_mutex failed");
        exit(1);
    }

    key_t sem_key2 = ftok("countfile", 66);
    int read_count_mutex = semget(sem_key2, 1, 0666 | IPC_CREAT);
    if (read_count_mutex == -1) {
        perror("semget read_count_mutex failed");
        exit(1);
    }

    // Shared read_count variable (store in shared memory)
    key_t key_rc = ftok("rcfile", 67);
    int shmid_rc = shmget(key_rc, sizeof(int), 0666 | IPC_CREAT);
    if (shmid_rc == -1) {
        perror("shmget for read_count failed");
        exit(1);
    }
    int *read_count = (int *)shmat(shmid_rc, NULL, 0);
    if (read_count == (int *)-1) {
        perror("shmat for read_count failed");
        exit(1);
    }

    while (1) {
        sem_wait(read_count_mutex);
        (*read_count)++;
        if (*read_count == 1) 
            sem_wait(rw_mutex);  // First reader blocks writer
        sem_signal(read_count_mutex);

        // ✅ Reading shared memory
        printf("Reader (PID %d) reads: %s\n", getpid(), data);
        sleep(1);  // Simulating reading time

        sem_wait(read_count_mutex);
        (*read_count)--;
        if (*read_count == 0) 
            sem_signal(rw_mutex);  // Last reader unblocks writer
        sem_signal(read_count_mutex);

        sleep(2);  // Simulate delay before next read
    }

    shmdt(data);
    shmdt(read_count);
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>

int main() {
    key_t sem_key1 = ftok("semfile", 65);
    int rw_mutex = semget(sem_key1, 1, 0666 | IPC_CREAT);
    semctl(rw_mutex, 0, SETVAL, 1);  // Set writer semaphore to 1

    key_t sem_key2 = ftok("countfile", 66);
    int read_count_mutex = semget(sem_key2, 1, 0666 | IPC_CREAT);
    semctl(read_count_mutex, 0, SETVAL, 1);  // Set read_count mutex to 1

    key_t key_rc = ftok("rcfile", 67);
    int shmid_rc = shmget(key_rc, sizeof(int), 0666 | IPC_CREAT);
    int *read_count = (int *)shmat(shmid_rc, NULL, 0);
    *read_count = 0;  // Initialize read_count to 0

    printf("Semaphores and shared memory initialized.\n");
    return 0;
}

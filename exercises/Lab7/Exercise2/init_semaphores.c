#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int main() {
    key_t sem_key1 = ftok("semfile", 65);
    int rw_mutex = semget(sem_key1, 1, 0666 | IPC_CREAT);
    semctl(rw_mutex, 0, SETVAL, 1);  // Set writer semaphore to 1

    key_t sem_key2 = ftok("countfile", 66);
    int read_count_mutex = semget(sem_key2, 1, 0666 | IPC_CREAT);
    semctl(read_count_mutex, 0, SETVAL, 1);  // Set read_count mutex to 1

    printf("Semaphores initialized.\n");
    return 0;
}

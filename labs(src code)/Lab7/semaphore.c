#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void sem_wait(int semid) {
    struct sembuf sb = {0, -1, 0};
    semop(semid, &sb, 1);
}

void sem_signal(int semid) {
    struct sembuf sb = {0, 1, 0};
    semop(semid, &sb, 1);
}

int main() {
    key_t key = ftok("semfile", 65);
    int semid = semget(key, 1, 0666 | IPC_CREAT);
    semctl(semid, 0, SETVAL, 1);

    if (fork() == 0) { // Child Process
        sem_wait(semid);
        printf("Child accessing critical section\n");
        sleep(2);
        printf("Child leaving critical section\n");
        sem_signal(semid);
    } else { // Parent Process
        sem_wait(semid);
        printf("Parent accessing critical section\n");
        sleep(2);
        printf("Parent leaving critical section\n");
        sem_signal(semid);
        wait(NULL);
        semctl(semid, 0, IPC_RMID, 0); // Remove semaphore
    }
    
    return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

int main() {
    srand(time(NULL)); // Seed random number generator
    pid_t pid1, pid2;
    int status1, status2;

    // First child process
    pid1 = fork();
    if (pid1 == 0) { // Child 1
        int random_num = rand() % 100; // Generate a random number (0-99)
        printf("Child 1 (PID: %d) exiting with status: %d\n", getpid(), random_num);
        exit(random_num);
    }

    // Second child process
    pid2 = fork();
    if (pid2 == 0) { // Child 2
        int random_num = rand() % 100; // Generate a random number (0-99)
        printf("Child 2 (PID: %d) exiting with status: %d\n", getpid(), random_num);
        exit(random_num);
    }

    // Parent process waits for both children
    waitpid(pid1, &status1, 0);
    waitpid(pid2, &status2, 0);

    int exit_status1 = WEXITSTATUS(status1);
    int exit_status2 = WEXITSTATUS(status2);
    int sum = exit_status1 + exit_status2;

    printf("Parent received exit statuses: %d and %d\n", exit_status1, exit_status2);
    printf("Parent exiting with sum: %d\n", sum);

    return sum; // Parent exits with the sum of children's statuses
}


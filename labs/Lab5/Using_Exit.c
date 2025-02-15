#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }

    if (pid == 0) { // Child process
        printf("Child process exiting with status 42\n");
        exit(42);
    } else {
        int status;
        wait(&status); // Parent waits for child
        printf("Parent: Child exited with status %d\n", WEXITSTATUS(status));
    }

    return 0;
}


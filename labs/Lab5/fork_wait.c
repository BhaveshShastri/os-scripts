#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork(); // Creating a child process

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }

    if (pid == 0) { // Child process
    	printf("Child printing parent and own process ID\n");
        printf("Child Process: PID = %d, Parent PID = %d\n", getpid(), getppid());
        printf("Child going to exit\n");
        exit(0); // Child process terminates
    } else { // Parent process
    	printf("Parent waiting for child");
        wait(NULL); // Waiting for child to finish
        printf("\nParent Process: Child completed\n");
    }

    return 0;
}


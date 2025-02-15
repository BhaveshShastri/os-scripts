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
        printf("Executing `ls -l` in the child process:\n");
        execl("/bin/ls", "ls", "-l", NULL); // Replaces child process with `ls -l`
        perror("exec failed"); // If exec fails
        exit(1);
    } else { // Parent process
        wait(NULL);
        printf("Parent process: Child execution complete\n");
    }

    return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd[2];  // File descriptors for the pipe
    pid_t pid;
    char write_msg[] = "Hello from parent!";
    char read_msg[100];

    if (pipe(fd) == -1) {
        perror("Pipe failed");
        return 1;
    }

    pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }

    if (pid > 0) { // Parent Process
        close(fd[0]); // Close unused read end
        write(fd[1], write_msg, strlen(write_msg) + 1);
        printf("Parent process sent message\n");
        close(fd[1]);
    } else { // Child Process
        close(fd[1]); // Close unused write end
        read(fd[0], read_msg, sizeof(read_msg));
        printf("Child received message as: %s\n", read_msg);
        close(fd[0]);
    }

    return 0;
}


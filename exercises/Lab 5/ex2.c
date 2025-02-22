#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    int status;
    char buffer[1024];

    // Create a child process
    pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }

    if (pid == 0) { // Child process
        int file = open("child_output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (file < 0) {
            perror("File open failed");
            exit(1);
        }

        // Redirect stdout to file
        dup2(file, STDOUT_FILENO);
        close(file);

        // Execute "ls -l"
        execlp("ls", "ls", "-l", NULL);

        // If exec fails
        perror("execlp failed");
        exit(1);
    } else { // Parent process
        wait(&status); // Wait for child to finish

        // Read and display contents of "child_output.txt"
        FILE *file = fopen("child_output.txt", "r");
        if (!file) {
            perror("File open failed");
            exit(1);
        }

        printf("\nContents of child_output.txt:\n");
        while (fgets(buffer, sizeof(buffer), file)) {
            printf("%s", buffer);
        }

        fclose(file);
    }

    return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int file = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (file < 0) {
        perror("File open failed");
        exit(1);
    }

    dup2(file, STDOUT_FILENO); // Redirects stdout to file
    close(file);

    printf("This will be written to output.txt instead of the terminal.\n");

    return 0;
}


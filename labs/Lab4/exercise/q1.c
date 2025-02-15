// Check if a File Exists and Create it if Not
// This program checks whether a file exists. If it exists, it prints "File found".
// Otherwise, it creates the file.

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd;
    const char *filename = "file.txt";

    // Check if the file exists by trying to open it in read mode
    fd = open(filename, O_RDONLY);

    if (fd >= 0) {
        // File exists
        printf("File found\n");
        close(fd); // Close the file after checking
    } else {
        // If the file doesn't exist, create it
        fd = open(filename, O_CREAT | O_WRONLY, 0644);
        if (fd < 0) {
            perror("Error creating the file");
            return 1;
        }
        printf("File not found. Creating file...\n");
        close(fd); // Close the file after creating
    }

    return 0;
}

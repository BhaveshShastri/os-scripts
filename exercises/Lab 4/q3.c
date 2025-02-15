// Modify the First Program to Handle Errors During Each File Operation:
// This modified version of the first program adds error handling for each file
// operation (open(), read(), write()). This program first checks if the file exists,
// then reads from it and writes to another file.

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd;
    const char *filename = "file.txt";

    // Try to open the file in read mode
    fd = open(filename, O_RDONLY);

    if (fd < 0) {
        // If the file doesn't exist, try to create it
        fd = open(filename, O_CREAT | O_WRONLY, 0644);
        if (fd < 0) {
            perror("Error opening or creating the file");
            return 1;
        }
        printf("File not found. Creating file...\n");
    } else {
        // File exists
        printf("File found\n");
    }

    // Try to read from the file
    char buffer[100];
    ssize_t bytesRead = read(fd, buffer, sizeof(buffer));
    if (bytesRead < 0) {
        perror("Error reading from file");
        close(fd);
        return 1;
    }

    // Try to write to the file (this step would only make sense if we were writing to another file)
    int destFd = open("copy.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (destFd < 0) {
        perror("Error opening destination file for writing");
        close(fd);
        return 1;
    }

    ssize_t bytesWritten = write(destFd, buffer, bytesRead);
    if (bytesWritten != bytesRead) {
        perror("Error writing to destination file");
        close(fd);
        close(destFd);
        return 1;
    }

    // Close files
    close(fd);
    close(destFd);

    printf("File operations completed successfully\n");

    return 0;
}
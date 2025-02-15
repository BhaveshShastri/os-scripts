// Copy the Contents of One File to Another Using read() and write() System Calls:
// This program copies the contents from a source file to a destination file using
// the read() and write() system calls.

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

int main() {
    int sourceFd, destFd, bytesRead, bytesWritten;
    char buffer[BUFFER_SIZE];

    const char *sourceFile = "file.txt";
    const char *destFile = "destination.txt";

    // Open the source file for reading
    sourceFd = open(sourceFile, O_RDONLY);
    if (sourceFd < 0) {
        perror("Error opening source file");
        return 1;
    }

    // Open the destination file for writing (create it if it doesn't exist)
    destFd = open(destFile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (destFd < 0) {
        perror("Error opening destination file");
        close(sourceFd);
        return 1;
    }

    // Read from source and write to destination
    while ((bytesRead = read(sourceFd, buffer, sizeof(buffer))) > 0) {
        bytesWritten = write(destFd, buffer, bytesRead);
        if (bytesWritten != bytesRead) {
            perror("Error writing to destination file");
            close(sourceFd);
            close(destFd);
            return 1;
        }
    }

    if (bytesRead < 0) {
        perror("Error reading from source file");
    }

    // Close both files
    close(sourceFd);
    close(destFd);

    printf("File contents copied successfully\n");

    return 0;
}

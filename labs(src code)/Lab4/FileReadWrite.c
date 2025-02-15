//Creating, Writing, and Reading a File

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd;
    char writeData[] = "Hello, this is a file system call example.";
    char readBuffer[100];

    // Create or open the file
    fd = open("example.txt", O_CREAT | O_WRONLY, 0644);
    if (fd < 0) {
        perror("Error opening file");
        return 1;
    }

    // Write to the file
    if (write(fd, writeData, sizeof(writeData)) < 0) {
        perror("Error writing to file");
        close(fd);
        return 1;
    }
    close(fd);

    // Reopen the file for reading
    fd = open("example.txt", O_RDONLY);
    if (fd < 0) {
        perror("Error opening file for reading");
        return 1;
    }

    // Read from the file
    if (read(fd, readBuffer, sizeof(readBuffer)) < 0) {
        perror("Error reading from file");
        close(fd);
        return 1;
    }

    // Print the content read
    printf("Content read from file: %s\n", readBuffer);

    close(fd);
    return 0;
}


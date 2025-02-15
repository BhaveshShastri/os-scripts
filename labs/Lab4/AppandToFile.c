//Appending Data to a File and Displaying Its Size

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main() {
    int fd;
    char appendData[] = " Appending this data to the file.";
    struct stat fileStat;

    // Open the file in append mode
    fd = open("example.txt", O_WRONLY | O_APPEND);
    if (fd < 0) {
        perror("Error opening file for appending");
        return 1;
    }

    // Append data to the file
    if (write(fd, appendData, sizeof(appendData)) < 0) {
        perror("Error appending to file");
        close(fd);
        return 1;
    }
    close(fd);

    // Get file information
    if (stat("example.txt", &fileStat) < 0) {
        perror("Error getting file stats");
        return 1;
    }

    // Print the file size
    printf("File size after appending: %ld bytes\n", fileStat.st_size);

    return 0;
}


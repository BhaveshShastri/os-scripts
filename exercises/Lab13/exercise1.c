//Exercise 1:
#include <stdio.h>
#include <stdlib.h>

// Function to calculate total head movement for FIFO
void fifo(int requests[], int n, int head) {
    int total_movement = 0;
    printf("\nFIFO Disk Scheduling:\n");
    printf("Servicing order: %d", head);

    for (int i = 0; i < n; i++) {
        total_movement += abs(requests[i] - head);
        head = requests[i];
        printf(" -> %d", head);
    }

    printf("\nTotal head movement: %d\n", total_movement);
}

// Comparison function for qsort
int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

// Function for SCAN (moving right first)
void scan(int requests[], int n, int head, int disk_size) {
    int total_movement = 0;
    int i, j;
    int* sorted = malloc(n * sizeof(int));
    for (i = 0; i < n; i++) sorted[i] = requests[i];
    qsort(sorted, n, sizeof(int), compare);

    printf("\nSCAN Disk Scheduling (towards right first):\n");
    printf("Servicing order: %d", head);

    // Find the index where head would fit
    for (i = 0; i < n && sorted[i] < head; i++);

    // Move right
    for (j = i; j < n; j++) {
        total_movement += abs(sorted[j] - head);
        head = sorted[j];
        printf(" -> %d", head);
    }

    // Move to end if not already
    if (head != disk_size - 1) {
        total_movement += abs((disk_size - 1) - head);
        head = disk_size - 1;
        printf(" -> %d", head);
    }

    // Then move left
    for (j = i - 1; j >= 0; j--) {
        total_movement += abs(sorted[j] - head);
        head = sorted[j];
        printf(" -> %d", head);
    }

    printf("\nTotal head movement: %d\n", total_movement);
    free(sorted);
}

// Function for C-SCAN (moving right and wrapping around)
void cscan(int requests[], int n, int head, int disk_size) {
    int total_movement = 0;
    int i, j;
    int* sorted = malloc(n * sizeof(int));
    for (i = 0; i < n; i++) sorted[i] = requests[i];
    qsort(sorted, n, sizeof(int), compare);

    printf("\nC-SCAN Disk Scheduling:\n");
    printf("Servicing order: %d", head);

    // Find the index where head would fit
    for (i = 0; i < n && sorted[i] < head; i++);

    // Move right
    for (j = i; j < n; j++) {
        total_movement += abs(sorted[j] - head);
        head = sorted[j];
        printf(" -> %d", head);
    }

    // Jump to 0 (wrap around)
    if (head != disk_size - 1) {
        total_movement += abs((disk_size - 1) - head);
        head = 0;
        total_movement += disk_size - 1;
        printf(" -> %d (jump)", head);
    }

    // Continue from beginning
    for (j = 0; j < i; j++) {
        total_movement += abs(sorted[j] - head);
        head = sorted[j];
        printf(" -> %d", head);
    }

    printf("\nTotal head movement: %d\n", total_movement);
    free(sorted);
}

int main() {
    int requests[] = {82, 170, 43, 140, 24, 16, 190};
    int n = sizeof(requests) / sizeof(requests[0]);
    int head = 50;
    int disk_size = 200;

    fifo(requests, n, head);
    scan(requests, n, head, disk_size);
    cscan(requests, n, head, disk_size);

    return 0;
}

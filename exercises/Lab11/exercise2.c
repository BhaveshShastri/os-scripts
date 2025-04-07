//Exercises 2: Add Fragmentation Calculation
#include <stdio.h>
#include <stdlib.h>

#define MAX_BLOCKS 10
#define MAX_PROCESSES 10

int allocation[MAX_PROCESSES];      // Allocation mapping: process -> block
int blockAllocation[MAX_BLOCKS];    // Block to process mapping
int blockSize[MAX_BLOCKS];
int originalBlockSize[MAX_BLOCKS];

void initialize(int m, int n) {
    for (int i = 0; i < m; i++) blockAllocation[i] = -1;
    for (int i = 0; i < n; i++) allocation[i] = -1;
}

void calculateFragmentation(int m, int n, int processSize[]) {
    int internalFrag = 0;
    int externalFrag = 0;
    int totalFree = 0;
    int canFitProcess = -1;

    // Internal fragmentation
    for (int i = 0; i < m; i++) {
        if (blockAllocation[i] != -1) {
            int pid = blockAllocation[i];
            internalFrag += blockSize[i];
        } else {
            externalFrag += blockSize[i];
        }
    }

    // External fragmentation (check for the first process that couldn't be allocated)
    for (int i = 0; i < n; i++) {
        if (allocation[i] == -1) {
            canFitProcess = processSize[i];
            break;
        }
    }

    printf("Internal Fragmentation: %d\n", internalFrag);
    if (canFitProcess != -1 && externalFrag >= canFitProcess) {
        printf("External Fragmentation: %d (Process of size %d cannot fit despite enough total free space)\n", externalFrag, canFitProcess);
    } else {
        printf("External Fragmentation: %d\n", externalFrag);
    }
    printf("\n");
}

void firstFit(int m, int n, int processSize[]) {
    initialize(m, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (blockAllocation[j] == -1 && blockSize[j] >= processSize[i]) {
                allocation[i] = j;
                blockAllocation[j] = i;
                blockSize[j] -= processSize[i];
                break;
            }
        }
    }

    printf("\n--- First Fit Allocation ---\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d -> ", i);
        if (allocation[i] != -1) printf("Block %d\n", allocation[i]);
        else printf("Not Allocated\n");
    }

    calculateFragmentation(m, n, processSize);
}

void bestFit(int m, int n, int processSize[]) {
    initialize(m, n);
    for (int i = 0; i < n; i++) {
        int bestIdx = -1;
        for (int j = 0; j < m; j++) {
            if (blockAllocation[j] == -1 && blockSize[j] >= processSize[i]) {
                if (bestIdx == -1 || blockSize[j] < blockSize[bestIdx]) {
                    bestIdx = j;
                }
            }
        }
        if (bestIdx != -1) {
            allocation[i] = bestIdx;
            blockAllocation[bestIdx] = i;
            blockSize[bestIdx] -= processSize[i];
        }
    }

    printf("\n--- Best Fit Allocation ---\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d -> ", i);
        if (allocation[i] != -1) printf("Block %d\n", allocation[i]);
        else printf("Not Allocated\n");
    }

    calculateFragmentation(m, n, processSize);
}

void worstFit(int m, int n, int processSize[]) {
    initialize(m, n);
    for (int i = 0; i < n; i++) {
        int worstIdx = -1;
        for (int j = 0; j < m; j++) {
            if (blockAllocation[j] == -1 && blockSize[j] >= processSize[i]) {
                if (worstIdx == -1 || blockSize[j] > blockSize[worstIdx]) {
                    worstIdx = j;
                }
            }
        }
        if (worstIdx != -1) {
            allocation[i] = worstIdx;
            blockAllocation[worstIdx] = i;
            blockSize[worstIdx] -= processSize[i];
        }
    }

    printf("\n--- Worst Fit Allocation ---\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d -> ", i);
        if (allocation[i] != -1) printf("Block %d\n", allocation[i]);
        else printf("Not Allocated\n");
    }

    calculateFragmentation(m, n, processSize);
}

void nextFit(int m, int n, int processSize[]) {
    initialize(m, n);
    int lastIndex = 0;
    for (int i = 0; i < n; i++) {
        int count = 0;
        while (count < m) {
            if (blockAllocation[lastIndex] == -1 && blockSize[lastIndex] >= processSize[i]) {
                allocation[i] = lastIndex;
                blockAllocation[lastIndex] = i;
                blockSize[lastIndex] -= processSize[i];
                break;
            }
            lastIndex = (lastIndex + 1) % m;
            count++;
        }
    }

    printf("\n--- Next Fit Allocation ---\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d -> ", i);
        if (allocation[i] != -1) printf("Block %d\n", allocation[i]);
        else printf("Not Allocated\n");
    }

    calculateFragmentation(m, n, processSize);
}

void resetBlockSizes(int m) {
    for (int i = 0; i < m; i++) blockSize[i] = originalBlockSize[i];
}

int main() {
    int m = 5; // number of blocks
    int n = 4; // number of processes
    int processSize[] = {212, 417, 112, 426};

    int blocks[] = {100, 500, 200, 300, 600};
    for (int i = 0; i < m; i++) {
        blockSize[i] = blocks[i];
        originalBlockSize[i] = blocks[i];
    }

    firstFit(m, n, processSize);
    resetBlockSizes(m);

    bestFit(m, n, processSize);
    resetBlockSizes(m);

    worstFit(m, n, processSize);
    resetBlockSizes(m);

    nextFit(m, n, processSize);

    return 0;
}

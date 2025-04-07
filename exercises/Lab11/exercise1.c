//Exercises 1: Implement Deallocation
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_BLOCKS 10
#define MAX_PROCESSES 10

int blockAllocation[MAX_BLOCKS]; // -1 means block is free
int allocation[MAX_PROCESSES];   // -1 means process not allocated

void initialize(int blockSize[], int m, int allocation[], int blockAllocation[]) {
    for (int i = 0; i < MAX_PROCESSES; i++) allocation[i] = -1;
    for (int i = 0; i < m; i++) blockAllocation[i] = -1;
}

void deallocateMemory(int blockSize[], int originalBlockSize[], int processID, int m) {
    int blockID = allocation[processID];
    if (blockID != -1 && blockID < m) {
        blockSize[blockID] += originalBlockSize[blockID] - blockSize[blockID]; // restore space
        blockAllocation[blockID] = -1;
        allocation[processID] = -1;
        printf("Deallocated memory of Process %d from Block %d\n", processID, blockID);
    } else {
        printf("Process %d is not allocated or invalid.\n", processID);
    }
}

void firstFit(int blockSize[], int originalBlockSize[], int m, int processSize[], int n) {
    initialize(blockSize, m, allocation, blockAllocation);
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

    printf("\nFirst Fit Allocation:\n");
    for (int i = 0; i < n; i++)
        printf("Process %d -> Block %d\n", i, allocation[i]);
}

void bestFit(int blockSize[], int originalBlockSize[], int m, int processSize[], int n) {
    initialize(blockSize, m, allocation, blockAllocation);
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

    printf("\nBest Fit Allocation:\n");
    for (int i = 0; i < n; i++)
        printf("Process %d -> Block %d\n", i, allocation[i]);
}

void worstFit(int blockSize[], int originalBlockSize[], int m, int processSize[], int n) {
    initialize(blockSize, m, allocation, blockAllocation);
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

    printf("\nWorst Fit Allocation:\n");
    for (int i = 0; i < n; i++)
        printf("Process %d -> Block %d\n", i, allocation[i]);
}

void nextFit(int blockSize[], int originalBlockSize[], int m, int processSize[], int n) {
    initialize(blockSize, m, allocation, blockAllocation);
    int lastAllocated = 0;

    for (int i = 0; i < n; i++) {
        int j = lastAllocated;
        int searched = 0;

        while (searched < m) {
            if (blockAllocation[j] == -1 && blockSize[j] >= processSize[i]) {
                allocation[i] = j;
                blockAllocation[j] = i;
                blockSize[j] -= processSize[i];
                lastAllocated = j;
                break;
            }
            j = (j + 1) % m;
            searched++;
        }
    }

    printf("\nNext Fit Allocation:\n");
    for (int i = 0; i < n; i++)
        printf("Process %d -> Block %d\n", i, allocation[i]);
}

int main() {
    int blockSize[MAX_BLOCKS] = {100, 500, 200, 300, 600};
    int originalBlockSize[MAX_BLOCKS] = {100, 500, 200, 300, 600}; // Used to restore size
    int processSize[MAX_PROCESSES] = {212, 417, 112, 426};
    int m = 5, n = 4;

    int blockSizeCopy[MAX_BLOCKS];

    // First Fit
    for (int i = 0; i < m; i++) blockSizeCopy[i] = blockSize[i];
    firstFit(blockSizeCopy, originalBlockSize, m, processSize, n);

    deallocateMemory(blockSizeCopy, originalBlockSize, 1, m); // Deallocate process 1
    deallocateMemory(blockSizeCopy, originalBlockSize, 3, m); // Deallocate process 3

    // Try allocating again using Best Fit
    for (int i = 0; i < m; i++) blockSizeCopy[i] = blockSize[i];
    bestFit(blockSizeCopy, originalBlockSize, m, processSize, n);

    return 0;
}

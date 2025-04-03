#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_BLOCKS 10
#define MAX_PROCESSES 10

void firstFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[n];
    for (int i = 0; i < n; i++) allocation[i] = -1;
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                allocation[i] = j;
                blockSize[j] -= processSize[i];
                break;
            }
        }
    }
    printf("First Fit Allocation:\n");
    for (int i = 0; i < n; i++)
        printf("Process %d -> Block %d\n", i, allocation[i]);
}

void nextFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[n], lastAllocated = 0;
    for (int i = 0; i < n; i++) allocation[i] = -1;
    
    for (int i = 0; i < n; i++) {
        for (int j = lastAllocated; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                allocation[i] = j;
                blockSize[j] -= processSize[i];
                lastAllocated = j;
                break;
            }
        }
    }
    printf("Next Fit Allocation:\n");
    for (int i = 0; i < n; i++)
        printf("Process %d -> Block %d\n", i, allocation[i]);
}

void bestFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[n];
    for (int i = 0; i < n; i++) allocation[i] = -1;
    
    for (int i = 0; i < n; i++) {
        int bestIdx = -1;
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (bestIdx == -1 || blockSize[j] < blockSize[bestIdx]) {
                    bestIdx = j;
                }
            }
        }
        if (bestIdx != -1) {
            allocation[i] = bestIdx;
            blockSize[bestIdx] -= processSize[i];
        }
    }
    printf("Best Fit Allocation:\n");
    for (int i = 0; i < n; i++)
        printf("Process %d -> Block %d\n", i, allocation[i]);
}

void worstFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[n];
    for (int i = 0; i < n; i++) allocation[i] = -1;
    
    for (int i = 0; i < n; i++) {
        int worstIdx = -1;
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (worstIdx == -1 || blockSize[j] > blockSize[worstIdx]) {
                    worstIdx = j;
                }
            }
        }
        if (worstIdx != -1) {
            allocation[i] = worstIdx;
            blockSize[worstIdx] -= processSize[i];
        }
    }
    printf("Worst Fit Allocation:\n");
    for (int i = 0; i < n; i++)
        printf("Process %d -> Block %d\n", i, allocation[i]);
}

int main() {
    int blockSize[MAX_BLOCKS] = {100, 500, 200, 300, 600};
    int processSize[MAX_PROCESSES] = {212, 417, 112, 426};
    int m = 5, n = 4;
    
    int blockSizeCopy[MAX_BLOCKS];
    
    // First Fit
    for (int i = 0; i < m; i++) blockSizeCopy[i] = blockSize[i];
    firstFit(blockSizeCopy, m, processSize, n);
    
    // Next Fit
    for (int i = 0; i < m; i++) blockSizeCopy[i] = blockSize[i];
    nextFit(blockSizeCopy, m, processSize, n);
    
    // Best Fit
    for (int i = 0; i < m; i++) blockSizeCopy[i] = blockSize[i];
    bestFit(blockSizeCopy, m, processSize, n);
    
    // Worst Fit
    for (int i = 0; i < m; i++) blockSizeCopy[i] = blockSize[i];
    worstFit(blockSizeCopy, m, processSize, n);
    
    return 0;
}

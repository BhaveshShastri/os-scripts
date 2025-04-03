#include <stdio.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

// Function to print the system state
void printState(int available[], int allocation[][MAX_RESOURCES], int need[][MAX_RESOURCES], int p, int r) {
    printf("\nCurrent System State:\n");
    printf("Available Resources: ");
    for (int i = 0; i < r; i++) {
        printf("%d ", available[i]);
    }
    printf("\n");

    printf("Allocation Matrix:\n");
    for (int i = 0; i < p; i++) {
        for (int j = 0; j < r; j++) {
            printf("%d ", allocation[i][j]);
        }
        printf("\n");
    }

    printf("Need Matrix:\n");
    for (int i = 0; i < p; i++) {
        for (int j = 0; j < r; j++) {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Function to calculate the Need Matrix
void calculateNeed(int need[MAX_PROCESSES][MAX_RESOURCES], int max[MAX_PROCESSES][MAX_RESOURCES], 
                   int allocation[MAX_PROCESSES][MAX_RESOURCES], int p, int r) {
    for (int i = 0; i < p; i++) {
        for (int j = 0; j < r; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}

// Banker's Algorithm to check system safety
int isSafe(int processes[], int available[], int max[][MAX_RESOURCES], int allocation[][MAX_RESOURCES], int p, int r) {
    int need[MAX_PROCESSES][MAX_RESOURCES];
    calculateNeed(need, max, allocation, p, r);
    
    int work[MAX_RESOURCES];
    for (int i = 0; i < r; i++) {
        work[i] = available[i];
    }
    
    int finish[MAX_PROCESSES] = {0};
    int safeSequence[MAX_PROCESSES];
    int count = 0;

    printf("\n=== Step-by-Step Execution of Banker's Algorithm ===\n");

    while (count < p) {
        int found = 0;
        for (int i = 0; i < p; i++) {
            if (finish[i] == 0) {
                int j;
                for (j = 0; j < r; j++) {
                    if (need[i][j] > work[j]) {
                        break;
                    }
                }

                if (j == r) { // Process can execute
                    printf("\nProcess P%d is executing...\n", i);
                    
                    // Print system state before allocation
                    printState(work, allocation, need, p, r);

                    for (int k = 0; k < r; k++) {
                        work[k] += allocation[i][k];
                    }

                    safeSequence[count++] = processes[i];
                    finish[i] = 1;
                    found = 1;

                    // Print system state after allocation
                    printf("Process P%d has finished execution. Updated system state:\n", i);
                    printState(work, allocation, need, p, r);
                }
            }
        }
        
        if (found == 0) {
            printf("System is in an unsafe state!\n");
            return 0;
        }
    }

    printf("System is in a safe state. Safe sequence is: ");
    for (int i = 0; i < p; i++) {
        printf("P%d ", safeSequence[i]);
    }
    printf("\n");
    return 1;
}

// Main function
int main() {
    int p, r;
    printf("Enter number of processes: ");
    scanf("%d", &p);
    printf("Enter number of resources: ");
    scanf("%d", &r);
    
    int processes[MAX_PROCESSES];
    for (int i = 0; i < p; i++) {
        processes[i] = i;
    }
    
    int available[MAX_RESOURCES];
    printf("Enter available resources: ");
    for (int i = 0; i < r; i++) {
        scanf("%d", &available[i]);
    }
    
    int max[MAX_PROCESSES][MAX_RESOURCES];
    printf("Enter maximum resource matrix: \n");
    for (int i = 0; i < p; i++) {
        for (int j = 0; j < r; j++) {
            scanf("%d", &max[i][j]);
        }
    }
    
    int allocation[MAX_PROCESSES][MAX_RESOURCES];
    printf("Enter allocation matrix: \n");
    for (int i = 0; i < p; i++) {
        for (int j = 0; j < r; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }
    
    isSafe(processes, available, max, allocation, p, r);
    
    return 0;
}


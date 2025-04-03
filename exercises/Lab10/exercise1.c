#include <stdio.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

// Function to calculate the need matrix
void calculateNeed(int need[MAX_PROCESSES][MAX_RESOURCES], int max[MAX_PROCESSES][MAX_RESOURCES], 
                   int allocation[MAX_PROCESSES][MAX_RESOURCES], int p, int r) {
    for (int i = 0; i < p; i++) {
        for (int j = 0; j < r; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}

// Function to check if the system is in a safe state
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
                if (j == r) {
                    for (int k = 0; k < r; k++) {
                        work[k] += allocation[i][k];
                    }
                    safeSequence[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }
        if (!found) {
            printf("System is in an unsafe state!\n");
            return 0;
        }
    }
    printf("System is in a safe state. Safe sequence is: ");
    for (int i = 0; i < p; i++) {
        printf("%d ", safeSequence[i]);
    }
    printf("\n");
    return 1;
}

// Function to handle resource requests
void requestResources(int processID, int request[], int available[], int max[][MAX_RESOURCES], int allocation[][MAX_RESOURCES], int p, int r) {
    int need[MAX_PROCESSES][MAX_RESOURCES];
    calculateNeed(need, max, allocation, p, r);

    // Check if request is within need
    for (int j = 0; j < r; j++) {
        if (request[j] > need[processID][j]) {
            printf("Error: Process %d requested more than its maximum need.\n", processID);
            return;
        }
    }
    
    // Check if resources are available
    for (int j = 0; j < r; j++) {
        if (request[j] > available[j]) {
            printf("Process %d must wait, not enough resources available.\n", processID);
            return;
        }
    }

    // Temporarily allocate requested resources
    for (int j = 0; j < r; j++) {
        available[j] -= request[j];
        allocation[processID][j] += request[j];
        need[processID][j] -= request[j];
    }
    
    // Check if system remains in a safe state
    int processes[MAX_PROCESSES];
    for (int i = 0; i < p; i++) processes[i] = i;
    
    if (!isSafe(processes, available, max, allocation, p, r)) {
        // Rollback allocation
        for (int j = 0; j < r; j++) {
            available[j] += request[j];
            allocation[processID][j] -= request[j];
            need[processID][j] += request[j];
        }
        printf("Request from Process %d is denied to prevent unsafe state.\n", processID);
    } else {
        printf("Request from Process %d is granted.\n", processID);
    }
}

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
    
    int processID;
    printf("Enter process ID making request: ");
    scanf("%d", &processID);
    
    int request[MAX_RESOURCES];
    printf("Enter requested resources: ");
    for (int i = 0; i < r; i++) {
        scanf("%d", &request[i]);
    }
    
    requestResources(processID, request, available, max, allocation, p, r);
    return 0;
}


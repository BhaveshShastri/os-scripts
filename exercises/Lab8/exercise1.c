#include <stdio.h>

typedef struct {
    int id, at, bt, ct, wt, tat;
} Process;

void swap(Process *a, Process *b) {
    Process temp = *a;
    *a = *b;
    *b = temp;
}

// Sort processes by arrival time
void sortProcesses(Process p[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[i].at > p[j].at) {
                swap(&p[i], &p[j]);
            }
        }
    }
}

void findAvgTime(Process p[], int n) {
    int idleTime = 0, currentTime = 0;

    // Sort processes based on arrival time
    sortProcesses(p, n);

    printf("\nGantt Chart:\n");
    printf("0");

    for (int i = 0; i < n; i++) {
        // Handle CPU idle time
        if (currentTime < p[i].at) {
            idleTime += p[i].at - currentTime;
            currentTime = p[i].at;
            printf(" --(idle)-- %d", currentTime);
        }

        // Compute Completion Time
        p[i].ct = currentTime + p[i].bt;
        currentTime = p[i].ct;

        // Compute Turnaround Time
        p[i].tat = p[i].ct - p[i].at;

        // Compute Waiting Time
        p[i].wt = p[i].tat - p[i].bt;

        // Print Gantt Chart timing
        printf(" -- P%d -- %d", p[i].id, currentTime);
    }

    printf("\n\nProcesses  Arrival Time  Burst Time  Waiting Time  Turnaround Time  Completion Time\n");
    float totalWT = 0, totalTAT = 0;
    for (int i = 0; i < n; i++) {
        totalWT += p[i].wt;
        totalTAT += p[i].tat;
        printf("   %d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", p[i].id, p[i].at, p[i].bt, p[i].wt, p[i].tat, p[i].ct);
    }

    printf("\nCPU Idle Time: %d", idleTime);
    printf("\nAverage Waiting Time: %.2f", totalWT / n);
    printf("\nAverage Turnaround Time: %.2f\n", totalTAT / n);
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    Process p[n];
    printf("Enter Arrival Time and Burst Time for each process:\n");

    for (int i = 0; i < n; i++) {
        printf("Process %d (AT BT): ", i + 1);
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].id = i + 1;
    }

    findAvgTime(p, n);
    return 0;
}


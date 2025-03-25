#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int id, at, bt, ct, wt, tat;
    bool completed;
} Process;

void swap(Process *a, Process *b) {
    Process temp = *a;
    *a = *b;
    *b = temp;
}

// Sort processes by arrival time
void sortByArrival(Process p[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[i].at > p[j].at) {
                swap(&p[i], &p[j]);
            }
        }
    }
}

void findAvgTime(Process p[], int n) {
    int completedProcesses = 0, currentTime = 0, idleTime = 0;
    
    // Sort processes by arrival time
    sortByArrival(p, n);

    printf("\nGantt Chart:\n");
    printf("0");

    while (completedProcesses < n) {
        int shortestIndex = -1, minBurstTime = __INT_MAX__;

        // Select the shortest job available
        for (int i = 0; i < n; i++) {
            if (!p[i].completed && p[i].at <= currentTime && p[i].bt < minBurstTime) {
                minBurstTime = p[i].bt;
                shortestIndex = i;
            }
        }

        // If no process is available, CPU is idle
        if (shortestIndex == -1) {
            printf(" --(idle)-- %d", ++currentTime);
            idleTime++;
        } else {
            // Process execution
            Process *proc = &p[shortestIndex];
            proc->ct = currentTime + proc->bt;
            proc->tat = proc->ct - proc->at;
            proc->wt = proc->tat - proc->bt;
            proc->completed = true;
            currentTime = proc->ct;
            completedProcesses++;

            // Print Gantt Chart timing
            printf(" -- P%d -- %d", proc->id, currentTime);
        }
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
        p[i].completed = false;
    }

    findAvgTime(p, n);
    return 0;
}


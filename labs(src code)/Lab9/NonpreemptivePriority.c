#include <stdio.h>

// Structure to represent a process
struct Process {
    int pid;        // Process ID
    int bt;         // Burst Time
    int priority;   // Priority
    int wt;         // Waiting Time
    int tat;        // Turnaround Time
};

// Function to sort processes based on priority (Non-Preemptive Scheduling)
void sortByPriority(struct Process proc[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (proc[i].priority > proc[j].priority) {
                struct Process temp = proc[i];
                proc[i] = proc[j];
                proc[j] = temp;
            }
        }
    }
}

// Function to calculate waiting time and turnaround time
void calculateTimes(struct Process proc[], int n) {
    proc[0].wt = 0; // First process has no waiting time
    
    for (int i = 1; i < n; i++) {
        proc[i].wt = proc[i - 1].wt + proc[i - 1].bt;
    }
    
    for (int i = 0; i < n; i++) {
        proc[i].tat = proc[i].wt + proc[i].bt;
    }
}

// Function to display the process details
void display(struct Process proc[], int n) {
    float total_wt = 0, total_tat = 0;
    printf("\nProcess	Burst Time	Priority	Waiting Time	Turnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", proc[i].pid, proc[i].bt, proc[i].priority, proc[i].wt, proc[i].tat);
        total_wt += proc[i].wt;
        total_tat += proc[i].tat;
    }
    printf("\nAverage Waiting Time: %.2f", total_wt / n);
    printf("\nAverage Turnaround Time: %.2f\n", total_tat / n);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    
    struct Process proc[n];
    
    for (int i = 0; i < n; i++) {
        proc[i].pid = i + 1;
        printf("Enter Burst Time and Priority for Process %d: ", i + 1);
        scanf("%d %d", &proc[i].bt, &proc[i].priority);
    }
    
    sortByPriority(proc, n);
    calculateTimes(proc, n);
    display(proc, n);
    
    return 0;
}


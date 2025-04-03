#include <stdio.h>
#include <limits.h>

// Structure to represent a process
struct Process {
    int pid;        // Process ID
    int at;         // Arrival Time
    int bt;         // Burst Time
    int priority;   // Priority
    int remaining_bt; // Remaining Burst Time
    int wt;         // Waiting Time
    int tat;        // Turnaround Time
    int completed;  // Completion flag (1 if completed)
};

// Function to find the process with the highest priority at a given time
int getHighestPriorityProcess(struct Process proc[], int n, int current_time) {
    int highest_priority_index = -1;
    int highest_priority = INT_MAX;

    for (int i = 0; i < n; i++) {
        if (proc[i].at <= current_time && proc[i].remaining_bt > 0) {
            // Check for the highest priority process (lowest priority number)
            if (proc[i].priority < highest_priority) {
                highest_priority = proc[i].priority;
                highest_priority_index = i;
            }
        }
    }
    return highest_priority_index;
}

// Function to perform preemptive priority scheduling and calculate CPU utilization
void preemptivePriorityScheduling(struct Process proc[], int n) {
    int current_time = 0, completed_processes = 0;
    float total_wt = 0, total_tat = 0;
    int total_burst_time = 0, idle_time = 0, start_time = -1, end_time = 0;

    // Initialize remaining burst time for all processes and compute total burst time
    for (int i = 0; i < n; i++) {
        proc[i].remaining_bt = proc[i].bt;
        proc[i].completed = 0;
        total_burst_time += proc[i].bt;
    }

    // Continue execution until all processes are completed
    while (completed_processes < n) {
        int idx = getHighestPriorityProcess(proc, n, current_time);

        if (idx == -1) {
            // No process available at this time, increase idle time
            idle_time++;
            current_time++;
            continue;
        }

        // Mark the first process start time
        if (start_time == -1)
            start_time = current_time;

        // Execute the selected process for 1 unit of time
        proc[idx].remaining_bt--;
        current_time++;

        // If process is completed
        if (proc[idx].remaining_bt == 0) {
            completed_processes++;
            proc[idx].tat = current_time - proc[idx].at;
            proc[idx].wt = proc[idx].tat - proc[idx].bt;
            total_wt += proc[idx].wt;
            total_tat += proc[idx].tat;
        }
    }

    end_time = current_time;  // Last process completion time

    // Calculate CPU Utilization
    float cpu_utilization = ((float)total_burst_time / (end_time - start_time)) * 100;

    // Display results
    printf("\nProcess\tArrival Time\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", proc[i].pid, proc[i].at, proc[i].bt, proc[i].priority, proc[i].wt, proc[i].tat);
    }
    
    printf("\nAverage Waiting Time: %.2f", total_wt / n);
    printf("\nAverage Turnaround Time: %.2f", total_tat / n);
    printf("\nCPU Utilization: %.2f%%\n", cpu_utilization);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process proc[n];

    for (int i = 0; i < n; i++) {
        proc[i].pid = i + 1;
        printf("Enter Arrival Time, Burst Time, and Priority for Process %d: ", i + 1);
        scanf("%d %d %d", &proc[i].at, &proc[i].bt, &proc[i].priority);
    }

    preemptivePriorityScheduling(proc, n);

    return 0;
}


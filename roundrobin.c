#include <stdio.h>

struct Process {
    int id;
    int burst_time;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
};

// Function to implement Round Robin Scheduling
void roundRobin(struct Process proc[], int n, int quantum) {
    int time = 0;   // Current time
    int completed = 0;
    int waiting_times[n];  // Track waiting times during execution

    // Initialize waiting times
    for (int i = 0; i < n; i++)
        waiting_times[i] = 0;

    while (completed < n) {
        int done = 1;
        
        for (int i = 0; i < n; i++) {
            if (proc[i].remaining_time > 0) {
                done = 0; // At least one process is still left

                if (proc[i].remaining_time > quantum) {
                    // Execute process for 'quantum' time
                    time += quantum;
                    proc[i].remaining_time -= quantum;
                } else {
                    // Process finishes execution
                    time += proc[i].remaining_time;
                    proc[i].remaining_time = 0;
                    proc[i].turnaround_time = time; // Completion Time
                    // Waiting time = Turnaround Time - Burst Time
                    proc[i].waiting_time = proc[i].turnaround_time - proc[i].burst_time;
                    
                    completed++;
                }
                
                printf("Time %d: Process %d executed\n", time, proc[i].id);
            }
        }
        
        if (done == 1)
            break; // All processes are completed
    }

    // Display process details
    printf("\nProcess ID\tBurst Time\tWaiting Time\tTurnaround Time\n");
    float total_waiting_time = 0, total_turnaround_time = 0;

    for (int i = 0; i < n; i++) {
        total_waiting_time += proc[i].waiting_time;
        total_turnaround_time += proc[i].turnaround_time;
        
        printf("%d\t\t%d\t\t%d\t\t%d\n",
               proc[i].id, proc[i].burst_time, proc[i].waiting_time, proc[i].turnaround_time);
    }

    // Calculate average waiting and turnaround times
    printf("\nAverage Waiting Time: %.2f", total_waiting_time / n);
    printf("\nAverage Turnaround Time: %.2f\n", total_turnaround_time / n);
}

int main() {
    int n, quantum;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process proc[n];

    // Input process details
    for (int i = 0; i < n; i++) {
        proc[i].id = i + 1;
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &proc[i].burst_time);
        proc[i].remaining_time = proc[i].burst_time; // Initially, remaining time = burst time
        proc[i].waiting_time = 0; // Initialize waiting time
    }

    printf("Enter time quantum: ");
    scanf("%d", &quantum);

    // Run the Round Robin scheduling
    roundRobin(proc, n, quantum);

    return 0;
}

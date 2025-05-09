#include <stdio.h>

struct Process{
    int id;
    int arrival;
    int burst;
    int priority;
    int wait;
    int tat;
    int complete;
    int processed;  // Flag to mark if process has been completed
}process[10];

// Function to find the highest priority job that has arrived but not processed yet
int findHighestPriorityJob(struct Process proc[], int n, int currentTime) {
    int highest = -1;
    int highestPriority = 10000;
    
    for(int i = 0; i < n; i++) {
        if(proc[i].arrival <= currentTime && proc[i].processed == 0) {
            if(proc[i].priority < highestPriority) {
                highestPriority = proc[i].priority;
                highest = i;
            }
        }
    }
    
    return highest;
}

void calculatePriorityScheduling(struct Process proc[], int n) {
    int currentTime = 0;
    int completed = 0;
    
    // Initialize processed flag for all processes
    for(int i = 0; i < n; i++) {
        proc[i].processed = 0;
    }
    
    // Continue until all processes are completed
    while(completed < n) {
        // Find the highest priority job available at current time
        int highest = findHighestPriorityJob(proc, n, currentTime);
        
        if(highest == -1) {
            // No process available, increment time
            currentTime++;
        } else {
            // Process the highest priority job
            currentTime += proc[highest].burst;
            
            // Process completed
            proc[highest].complete = currentTime;
            proc[highest].tat = proc[highest].complete - proc[highest].arrival;
            proc[highest].wait = proc[highest].tat - proc[highest].burst;
            
            // Mark process as processed
            proc[highest].processed = 1;
            completed++;
        }
    }
}

void sortByArrival(struct Process proc[], int n){
    struct Process temp;
    for(int i = 0; i < n-1; i++){
        for(int j = 0; j < n-i-1; j++)
        {
            if(proc[j].arrival > proc[j+1].arrival || 
              (proc[j].arrival == proc[j+1].arrival && proc[j].priority > proc[j+1].priority))
            {
                temp = proc[j];
                proc[j] = proc[j+1];
                proc[j+1] = temp;
            }
        }
    }
}

void sortByCompletion(struct Process proc[], int n) {
    struct Process temp;
    for(int i = 0; i < n-1; i++){
        for(int j = 0; j < n-i-1; j++)
        {
            if(proc[j].complete > proc[j+1].complete)
            {
                temp = proc[j];
                proc[j] = proc[j+1];
                proc[j+1] = temp;
            }
        }
    }
}

void display(struct Process proc[], int n){
    printf("\nProcess\tArrival\tBurst\tPriority\tWait\tTAT\tComplete\n");
    int totalwait = 0;
    int totaltat = 0;
    for(int i = 0; i < n; i++)
    {
        totalwait += proc[i].wait;
        totaltat += proc[i].tat;
        printf("%d\t%d\t%d\t%d\t\t%d\t%d\t%d\n", proc[i].id, proc[i].arrival, proc[i].burst, proc[i].priority, proc[i].wait, proc[i].tat, proc[i].complete);
    }
    printf("\nAverage Waiting Time: %.2f", (float)totalwait/n);
    printf("\nAverage Turnaround Time: %.2f\n", (float)totaltat/n);
    
    // Sort by completion time for Gantt chart
    struct Process sortedProc[10];
    for(int i = 0; i < n; i++) {
        sortedProc[i] = proc[i];
    }
    sortByCompletion(sortedProc, n);
    
    printf("\nGantt Chart:\n");
        
    // Print process boxes
    printf("|");
    for (int i = 0; i < n; i++) {
        printf(" P%d |\t", sortedProc[i].id);
    }

    // Print time markers
    printf("\n");
    printf("%d", sortedProc[0].arrival);  // First process arrival time

    for (int i = 0; i < n; i++) {
        printf("     %d", sortedProc[i].complete);
    }
    printf("\n");
}

void main()
{
    int n;
    printf("Enter no. of processes: ");
    scanf("%d", &n);
    for(int i = 0; i < n; i++)
    {
        process[i].id = i+1;
        printf("Enter arrival time for process %d: ", i+1);
        scanf("%d", &process[i].arrival);
        printf("Enter burst time for process %d: ", i+1);
        scanf("%d", &process[i].burst);
        printf("Enter priority for process %d: ", i+1);
        scanf("%d", &process[i].priority);
    }
    sortByArrival(process, n);
    calculatePriorityScheduling(process, n);
    display(process, n);
}
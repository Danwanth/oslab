#include <stdio.h>
#include <stdbool.h>

#define P 10  // Maximum number of processes
#define R 10  // Maximum number of resources

void inputData(int *n, int *m, int avail[], int max[][R], int allot[][R]);
bool isSafe(int n, int m, int avail[], int max[][R], int allot[][R]);

int main() {
    int n, m; // Number of processes and resources
    int avail[R], max[P][R], allot[P][R];

    // User input for data
    inputData(&n, &m, avail, max, allot);

    // Call the function to check if the system is in a safe state
    isSafe(n, m, avail, max, allot);

    return 0;
}

void inputData(int *n, int *m, int avail[], int max[][R], int allot[][R]) {
    printf("Enter the number of processes: ");
    scanf("%d", n);

    printf("Enter the number of resources: ");
    scanf("%d", m);

    printf("Enter the Allocation Matrix (%d x %d):\n", *n, *m);
    for (int i = 0; i < *n; i++) {
        for (int j = 0; j < *m; j++) {
            scanf("%d", &allot[i][j]);
        }
    }

    printf("Enter the Max Matrix (%d x %d):\n", *n, *m);
    for (int i = 0; i < *n; i++) {
        for (int j = 0; j < *m; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    printf("Enter the Available Resources (%d):\n", *m);
    for (int j = 0; j < *m; j++) {
        scanf("%d", &avail[j]);
    }
}

bool isSafe(int n, int m, int avail[], int max[][R], int allot[][R]) {
    int need[P][R];  

    // Compute Need Matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - allot[i][j];
        }
    }

    bool finish[P] = {false};  
    int work[R]; 

    // Initialize work as the available resources
    for (int i = 0; i < m; i++) {
        work[i] = avail[i];
    }

    int count = 0;  
    while (count < n) {
        bool found = false;

        for (int p = 0; p < n; p++) {
            if (!finish[p]) {
                bool canAllocate = true;

                // Check if the process can be allocated
                for (int j = 0; j < m; j++) {
                    if (need[p][j] > work[j]) {
                        canAllocate = false;
                        break;
                    }
                }

                // Allocate resources if valid
                if (canAllocate) {
                    for (int j = 0; j < m; j++) {
                        work[j] += allot[p][j];
                    }
                    finish[p] = true;  
                    found = true;  
                    count++; 
                    printf("Process P%d executed successfully.\n", p);
                    break;
                }
            }
        }

        // If no process can proceed, system is unsafe
        if (!found) {
            printf("System is in an UNSAFE state.\n");
            return false;
        }
    }

    printf("System is in a SAFE state.\n");
    return true;
}

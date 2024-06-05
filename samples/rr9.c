#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

typedef struct Process {
    int process;   // Process number
    int burst;     // Burst time
    int arrival;   // Arrival time
    int remaining; // Remaining time
    int start[20]; // Start time (array for tracking execution history)
    int wait;      // Waiting Time
    int complete;  // Completion time
    int tat;       // Turn around time
} Process;

int quantum;

int main() {
    int n, i, j;

    // Taking Input
    printf("Enter the no. of processes: ");
    scanf("%d", &n);

    Process p[n]; // Array of Process structures

    printf("Enter the quantum\n");
    scanf("%d", &quantum);

    printf("Enter the process numbers\n");
    for (i = 0; i < n; i++)
        scanf("%d", &(p[i].process));

    printf("Enter the Arrival time of processes\n");
    for (i = 0; i < n; i++)
        scanf("%d", &(p[i].arrival));

    printf("Enter the Burst time of processes\n");
    for (i = 0; i < n; i++)
        scanf("%d", &(p[i].burst));

    // Initialize remaining time, start time array, and waiting time
    for (i = 0; i < n; i++) {
        p[i].remaining = p[i].burst;
        for (j = 0; j < 20; j++) {
            p[i].start[j] = -1; // Initialize start time slots to -1
        }
        p[i].wait = 0;
    }

    int c = n, time = 0; // Number of processes remaining, current time
    float mini = INT_MAX;  // Minimum arrival time for scheduling
    bool flag = false;     // Flag to indicate if a process was scheduled

    while (c != 0) {
        mini = INT_MAX;
        flag = false;

        // Find the process with the minimum arrival time that hasn't finished
        for (i = 0; i < n; i++) {
            float p = time + 0.1;
            if (p[i].arrival <= p && p[i].remaining > 0 && mini > p[i].arrival) {
                index = i;
                mini = p[i].arrival;
                flag = true;
            }
        }

        // If no process is ready, increment time
        if (!flag) {
            time++;
            continue;
        }

        int j = 0; // Index for start time array
        while (p[index].start[j] != -1) { // Find an empty slot in start time array
            j++;
        }

        p[index].start[j] = time; // Record start time

        // Execute the process for the quantum or remaining time, whichever is less
        if (p[index].remaining <= quantum) {
            time += p[index].remaining;
            p[index].remaining = 0;
        } else {
            time += quantum;
            p[index].remaining -= quantum;
        }

        // Calculate waiting time and completion time if the process finishes
        if (p[index].remaining == 0) {
            c--;
            p[index].complete = time;
            p[index].wait = p[index].complete - p[index].arrival - p[index].burst;
        }
    } // End of while loop

    // Printing output
    printf("Process number\tArrival time\tBurst time\t");
    j = 0;
    while (j != 10) {
        j += 1;
        printf(" ");
    }
    printf("Start time\t\tFinal time\tWait Time\tTurnAround Time\n");

    for (i = 0; i < n; i++) {
        printf("%d\t\t", p[i].process);
        printf("%d\t\t", p[i].arrival);
        printf("%d\t", p[i].burst);
        j = 

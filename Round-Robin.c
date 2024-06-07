#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

// Structure to store process details
typedef struct RR
{
    int process;   // Process ID
    int arrival;   // Arrival time
    int burst;     // Burst time
    int start[20]; // Array to store the start times
    int wt;        // Waiting time
    int complete;  // Completion time
    int tat;       // Turnaround time
} RR;

int quantum; // Quantum for Round Robin scheduling

int main()
{
    int n, i, j;

    // Taking Input
    n = 4; // No. of Processes
    RR p[n];
    quantum = 2; // Time Quantum

    // Initialize process data
    int process_data[][3] = {
        // Process,  Arrival Time, Burst Time
        {1, 0, 10},
        {2, 6, 8},
        {3, 7, 4},
        {4, 9, 5}};

    // Assign process data to arr array
    for (i = 0; i < n; i++)
    {
        p[i].process = process_data[i][0];
        p[i].arrival = process_data[i][1];
        p[i].burst = process_data[i][2];
        p[i].complete = 0; // Completion time is initially set to 0
    }

    // Declaring variables
    int c = n, s[n][20];
    float time = 0, mini = INT_MAX, b[n], a[n];

    // Initializing burst and arrival time arrays
    int index = -1;
    for (i = 0; i < n; i++)
    {
        b[i] = p[i].burst;
        a[i] = p[i].arrival;
        for (j = 0; j < 20; j++)
        {
            s[i][j] = -1; // Initialize start time array with -1
        }
    }

    int tot_wt, tot_tat;
    tot_wt = 0;
    tot_tat = 0;
    bool flag = false;

    // Round Robin Scheduling Algorithm
    while (c != 0)
    {
        mini = INT_MAX;
        flag = false;

        // Find the process with minimum arrival time
        for (i = 0; i < n; i++)
        {
            float p = time + 0.1;
            if (a[i] <= p && mini > a[i] && b[i] > 0)
            {
                index = i;
                mini = a[i];
                flag = true;
            }
        }

        // If no process is available, increment time
        if (!flag)
        {
            time++;
            continue;
        }

        // Calculate start time
        j = 0;
        while (s[index][j] != -1)
        {
            j++;
        }

        if (s[index][j] == -1)
        {
            s[index][j] = time;
            p[index].start[j] = time;
        }

        // Execute the process for quantum time or remaining burst time
        if (b[index] <= quantum)
        {
            time += b[index];
            b[index] = 0;
        }
        else
        {
            time += quantum;
            b[index] -= quantum;
        }

        // If process is not completed, update arrival time
        if (b[index] > 0)
        {
            a[index] = time + 0.1;
        }

        // If process is completed, update completion time, waiting time, and turnaround time
        if (b[index] == 0)
        {
            c--;
            p[index].complete = time;
            p[index].wt = p[index].complete - p[index].arrival - p[index].burst;
            tot_wt += p[index].wt;
            p[index].tat = p[index].burst + p[index].wt;
            tot_tat += p[index].tat;
        }
    } // end of while loop

    // Printing output
    printf("Process\t\tArrival Time\tBurst Time\tCompletion time\t\tTurn Around Time\tWaiting Time\n");

    // Print process details
    for (i = 0; i < n; i++)
    {
        printf("%5d\t%12d\t\t%8d\t\t%d\t\t\t%12d\t%12d\n", p[i].process, p[i].arrival, p[i].burst, p[i].complete, p[i].tat, p[i].wt);
    }

    // Calculating average wait time
    double avg_wt, avg_tat;
    avg_wt = tot_wt / (float)n;

    // Printing average wait time and turnaround time
    printf("Average Waiting Time: %.2f\n", avg_wt);

    return 0;
}
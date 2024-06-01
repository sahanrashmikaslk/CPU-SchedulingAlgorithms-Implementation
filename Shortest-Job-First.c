#include <stdio.h>
#include <stdlib.h>

// Define a structure to store process information
typedef struct sjf
{
    int process; // Process ID
    int burst;   // Burst time (CPU time required)
    int arrival; // Arrival time
    int tat;     // Turn around time (Completion time - Arrival time)
    int wt;      // Waiting time (Turn around time - Burst time)
} sjf;

// Function prototype for sorting processes based on arrival time
void sort(sjf[], int);

int main()
{
    int n, i, j, TCT, count_process = 0, count = 0, minBurst, pos;
    float AvWT = 0;

    n = 4; // No. of Processes

    sjf arr[n]; // Array of type sjf

    // Initialize process data
    int process_data[][3] = {
        // Process,  Arrival Time, Brust Time
        {1, 0, 10},
        {2, 6, 8},
        {3, 7, 4},
        {4, 9, 5}};

    // Assign process data to sjf array
    for (i = 0; i < n; i++)
    {
        arr[i].process = process_data[i][0];
        arr[i].arrival = process_data[i][1];
        arr[i].burst = process_data[i][2];
    }

    // Sort processes based on arrival time
    sort(arr, n);

    // Initialize variables for the first process
    TCT = arr[0].tat = arr[0].burst;
    arr[0].wt = arr[0].tat - arr[0].burst;
    arr[0].arrival = -1; // Mark the first process as completed

    // Sort processes again based on arrival time
    sort(arr, n);
    count_process = 1;

    // Main loop for executing processes
    while (count_process < n)
    {
        minBurst = 999; // Initialize with a large value
        count = 0;
        i = count_process;

        // Count the number of processes arrived by the current time
        while (TCT >= arr[i].arrival && i < n)
        {
            count++;
            i++;
        }

        // Find the process with the minimum burst time among the arrived processes
        for (j = i - count; count != 0 && j < n; j++, count--)
        {
            if (arr[j].burst < minBurst)
            {
                minBurst = arr[j].burst;
                pos = j;
            }
        }

        // Execute the process with the minimum burst time
        TCT = TCT + arr[pos].burst;
        arr[pos].tat = TCT - arr[pos].arrival;
        arr[pos].wt = arr[pos].tat - arr[pos].burst;
        arr[pos].arrival = -1; // Mark the process as completed

        // Sort processes again based on arrival time
        sort(arr, n);
        count_process++;
    }

    // Print the processes with their details
    printf("Process\t\tBurst Time\tTurn Around Time\tWaiting Time\n");
    for (i = 0; i < n; i++)
    {
        AvWT = AvWT + arr[i].wt;
        printf("%5d\t%15d\t\t%9d\t%12d\n", arr[i].process, arr[i].burst, arr[i].tat, arr[i].wt);
    }

    printf("Average Waiting Time: %.2f\n", AvWT / n);
    return 0;
}

// Function to sort processes based on arrival time
void sort(sjf arr[], int n)
{
    int i, j;
    sjf temp;

    for (i = 0; i < n - 1; i++)
        for (j = i + 1; j < n; j++)
        {
            // Sorting the processes according to their arrival time
            if (arr[i].arrival > arr[j].arrival)
            {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
}
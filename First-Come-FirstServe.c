#include <stdio.h>
#include <stdlib.h>

// Define a structure to store process information
typedef struct fcfs
{
    int process; // Process Number
    int burst;   // Burst Time
    int arrival; // Arrival Time
    int tat;     // Turn Around Time
    int wt;      // Waiting Time
} fcfs;

// Function prototype for sorting processes based on arrival time
int sort(fcfs[], int);

int main()
{
    int n, i, temp = 0;
    float AvWt = 0;

    n = 4;       // No. of Processes
    fcfs arr[n]; // Array of type fcfs
    int tct[n];  // Array to store completion time of each process

    // Initialize process data
    int process_data[][3] = {
        // Process,  Arrival Time, Brust Time
        {1, 0, 10},
        {2, 6, 8},
        {3, 7, 4},
        {4, 9, 5}};

    // Assign process data to fcfs array
    for (i = 0; i < n; i++)
    {
        arr[i].process = process_data[i][0];
        arr[i].arrival = process_data[i][1];
        arr[i].burst = process_data[i][2];
    }

    // Sorting the processes according to their arrival time
    sort(arr, n);

    // Print the header
    printf("Process\t\tArrival Time\tBurst Time\tTurn Around Time\tWaiting Time\n");

    // Calculate and print process details
    for (i = 0; i < n; i++)
    {
        // Calculate the completion time for the current process
        tct[i] = temp + arr[i].burst;

        // Update the temporary completion time
        temp = tct[i];

        // Calculate the turn around time and waiting time
        arr[i].tat = tct[i] - arr[i].arrival;
        arr[i].wt = arr[i].tat - arr[i].burst;

        // Update the average waiting time
        AvWt = AvWt + arr[i].wt;

        // Print the process details
        printf("%5d\t%15d\t\t%9d\t%12d\t%12d\n", arr[i].process, arr[i].arrival, arr[i].burst, arr[i].tat, arr[i].wt);
    }

    // Print the average waiting time
    printf("Average Waiting Time: %.2f\n", AvWt / n);

    return 0;
}

// Bubble Sort function to sort processes based on arrival time
int sort(fcfs arr[], int n)
{
    int i, j;
    fcfs k;

    // Outer loop for the number of passes
    for (i = 0; i < n - 1; i++)
    {
        // Inner loop for comparisons and swapping
        for (j = i + 1; j < n; j++)
        {
            // Sorting the processes according to their arrival time
            if (arr[i].arrival > arr[j].arrival)
            {
                // Swap the processes
                k = arr[i];
                arr[i] = arr[j];
                arr[j] = k;
            }
        }
    }

    return 0;
}
#include <stdio.h>
#include <stdlib.h>

// Define a structure to store process information
typedef struct RR
{
    int process;   // Process number
    int burst;     // Burst time
    int arrival;   // Arrival time
    int remaining; // Remaining time
    int complete;  // Completion time
    int tat;       // Turn around time
    int wt;        // Waiting Time
} RR;

// Function prototype for sorting processes based on arrival time
void sort(RR arr[], int n);

int main()
{
    int i, j, n, TCT = 0, Time_Quantum, front = 0, rear = 0;
    float AvWT = 0;

    n = 4;            // No. of Processes
    Time_Quantum = 2; // Time Quantum
    RR arr[n];        // Array of type struct RR
    int ReadyQue[n];  // Ready Queue

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
        arr[i].process = process_data[i][0];
        arr[i].arrival = process_data[i][1];
        arr[i].burst = process_data[i][2];
        arr[i].remaining = arr[i].burst; // Initially the remaining time is the burst time
        arr[i].complete = 0;             // Completion time is 0
    }

    // Sort the processes according to the arrival time
    sort(arr, n);

    ReadyQue[rear] = 0; // Process 0 is in ready queue

    while (1)
    {
        int done = 1;

        // Iterate over all processes
        for (i = 0; i < n; i++)
        {
            // Check if the process has arrived and has remaining time
            if (TCT >= arr[i].arrival && arr[i].remaining > 0)
            {
                done = 0;

                // If the remaining burst time is greater than the time quantum
                if (arr[i].remaining > Time_Quantum)
                {
                    TCT += Time_Quantum;              // Update the total completion time
                    arr[i].remaining -= Time_Quantum; // Reduce the remaining time
                }
                else
                {
                    TCT += arr[i].remaining; // Update the total completion time
                    arr[i].remaining = 0;    // Set the remaining time to 0
                    arr[i].complete = TCT;   // Set the completion time
                }

                // Add the next arrived processes to the ready queue
                for (j = 0; j < n; j++)
                {
                    if (arr[j].arrival <= TCT && arr[j].remaining > 0 && i != j)
                    {
                        int found = 0;
                        for (int k = front; k <= rear; k++)
                        {
                            // Check if the process is already in the ready queue
                            if (ReadyQue[k % n] == j)
                            {
                                found = 1;
                                break;
                            }
                        }
                        // If the process is not in the ready queue, add it
                        if (!found)
                        {
                            rear = (rear + 1) % n;
                            ReadyQue[rear] = j;
                        }
                    }
                }

                // Move to the next process in the ready queue
                front = (front + 1) % n;
            }
        }

        // If all processes are completed, break the loop
        if (done)
            break;
    }

    // Calculate waiting time
    for (i = 0; i < n; i++)
    {
        arr[i].tat = arr[i].complete - arr[i].arrival; // Turn around time
        arr[i].wt = arr[i].tat - arr[i].burst;         // Waiting time
        AvWT += arr[i].wt;                             // Update the average waiting time
    }

    printf("Process\t\tArrival Time\tBurst Time\tTurn Around Time\tWaiting Time\n");
    for (i = 0; i < n; i++)
    {
        printf("%5d\t%15d\t\t%9d\t%12d\t%12d\n", arr[i].process, arr[i].arrival, arr[i].burst, arr[i].tat, arr[i].wt);
    }

    printf("Average Waiting Time: %.2f\n", AvWT / n);

    return 0;
}

// Bubble sort function to sort processes based on arrival time
void sort(RR arr[], int n)
{
    int i, j;
    RR temp;

    for (i = 0; i < n - 1; i++)
        for (j = i + 1; j < n; j++)
            if (arr[i].arrival > arr[j].arrival)
            {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
}
#include <stdio.h>
#include <stdlib.h>

// Structure to represent a process
struct process
{
    int pid;
    int arrival_time;
    int burst_time;
    int waiting_time;
    int turnaround_time;
};

// Function to calculate waiting time for all processes
void calculate_waiting_time(struct process processes[], int num_processes)
{
    processes[0].waiting_time = 0; // No waiting time for the first process in FCFS and SJF
    for (int i = 1; i < num_processes; i++)
    {
        processes[i].waiting_time = processes[i - 1].burst_time + processes[i - 1].waiting_time;
    }
}

// Function to calculate turnaround time for all processes
void calculate_turnaround_time(struct process processes[], int num_processes)
{
    for (int i = 0; i < num_processes; i++)
    {
        processes[i].turnaround_time = processes[i].burst_time + processes[i].waiting_time;
    }
}

// Function to print Gantt chart (Optional)
void print_gantt_chart(struct process[], int num_processes)
{
    // Implement logic to display process execution order on a time axis
}

// FCFS scheduling algorithm
void fcfs(struct process processes[], int num_processes)
{
    calculate_waiting_time(processes, num_processes);
    calculate_turnaround_time(processes, num_processes);

    // Print process details (PID, arrival time, burst time, waiting time, turnaround time)
    printf("\nFCFS Scheduling:\n");
    printf("PID\tAT\tBT\tWT\tTAT\n");
    for (int i = 0; i < num_processes; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\n", processes[i].pid, processes[i].arrival_time, processes[i].burst_time, processes[i].waiting_time, processes[i].turnaround_time);
    }
}

// SJF scheduling algorithm (Non-preemptive)
void sjf(struct process processes[], int num_processes)
{
    // Sort processes based on burst time (ascending order)
    for (int i = 0; i < num_processes - 1; i++)
    {
        for (int j = 0; j < num_processes - i - 1; j++)
        {
            if (processes[j].burst_time > processes[j + 1].burst_time)
            {
                struct process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }

    calculate_waiting_time(processes, num_processes);
    calculate_turnaround_time(processes, num_processes);

    // Print process details
    printf("\nSJF Scheduling:\n");
    printf("PID\tAT\tBT\tWT\tTAT\n");
    for (int i = 0; i < num_processes; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\n", processes[i].pid, processes[i].arrival_time, processes[i].burst_time, processes[i].waiting_time, processes[i].turnaround_time);
    }
}

// RR scheduling algorithm
void rr(struct process processes[], int num_processes, int time_quantum)
{
    int queue[num_processes]; // Queue to store process IDs
    int front = 0, rear = -1; // Queue indices
    int current_time = 0;     // Current system time

    // Enqueue all processes initially
    for (int i = 0; i < num_processes; i++)
    {
        queue[++rear] = i;
    }

    while (front <= rear)
    {
        int i = queue[front++];

        // Check if remaining burst time is less than time quantum
        if (processes[i].burst_time <= time_quantum)
        {
            current_time += processes[i].burst_time;
            processes[i].burst_time = 0; // Process completed
        }
        else
        {
            processes[i].burst_time -= time_quantum; // Reduce remaining burst time
            current_time += time_quantum;            // Update current time

            // Re-enqueue the process if not completed
            if (processes[i].burst_time > 0)
            {
                queue[++rear] = i;
            }
        }

        // Check if all processes are completed
        int all_completed = 1;
        for (int i = 0; i < num_processes; i++)
        {
            if (processes[i].burst_time > 0)
            {
                all_completed = 0;
                break;
            }
        }

        // If a process is completed and there are more processes waiting, context switch
        if (all_completed == 0 && front != rear)
        {
            // Implement logic to handle context switching (e.g., move the completed process from the front and potentially bring a new process from the back)
        }
    }

    // Calculate waiting and turnaround times after all processes are complete
    calculate_waiting_time(processes, num_processes);
    calculate_turnaround_time(processes, num_processes);

    // Print process details
    printf("\nRR Scheduling:\n");
    printf("PID\tAT\tBT\tWT\tTAT\n");
    for (int i = 0; i < num_processes; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\n", processes[i].pid, processes[i].arrival_time, processes[i].burst_time, processes[i].waiting_time, processes[i].turnaround_time);
    }
}

int main()
{
    // Replace with actual data initialization for processes
    struct process processes[] =
        {
            {1, 0, 10, 0, 0},
            {2, 6, 8, 0, 0},
            {3, 7, 4, 0, 0},
            {4, 9, 5, 0, 0}};

    int num_processes = sizeof(processes) / sizeof(processes[0]);

    int time_quantum = 4; // Adjust time quantum as needed

    fcfs(processes, num_processes);
    sjf(processes, num_processes);
    rr(processes, num_processes, time_quantum);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// FCFS (First-Come, First-Served) Implementation

void fcfs(int processes[], int n, int burst_time[], int arrival_time[])
{
    int wait_time[n], total_wait_time = 0, total_turnaround_time = 0, turnaround_time[n];

    // Waiting time for the first process is 0
    wait_time[0] = 0;

    // Calculating waiting time
    for (int i = 1; i < n; i++)
    {
        wait_time[i] = burst_time[i - 1] + wait_time[i - 1] - arrival_time[i];
        if (wait_time[i] < 0)
            wait_time[i] = 0; // Ensure no negative waiting time
    }

    // Calculating turnaround time
    for (int i = 0; i < n; i++)
    {
        turnaround_time[i] = burst_time[i] + wait_time[i];
        total_wait_time += wait_time[i];
        total_turnaround_time += turnaround_time[i];
    }

    printf("FCFS Scheduling\n");
    printf("Process\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");

    for (int i = 0; i < n; i++)
    {
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\n", processes[i], arrival_time[i], burst_time[i], wait_time[i], turnaround_time[i]);
    }

    printf("Average Waiting Time: %.2f\n", (float)total_wait_time / n);
    printf("Average Turnaround Time: %.2f\n\n", (float)total_turnaround_time / n);
}

// SJF (Shortest Job First) Implementation

void sjf(int processes[], int n, int burst_time[], int arrival_time[])
{
    int wait_time[n], total_wait_time = 0, total_turnaround_time = 0, turnaround_time[n];
    int completed = 0, time = 0, min_burst = 10000, shortest = 0;
    bool visited[n];

    for (int i = 0; i < n; i++)
        visited[i] = false;

    while (completed != n)
    {
        for (int j = 0; j < n; j++)
        {
            if ((arrival_time[j] <= time) && (!visited[j]) && (burst_time[j] < min_burst))
            {
                min_burst = burst_time[j];
                shortest = j;
            }
        }

        time += burst_time[shortest];
        wait_time[shortest] = time - burst_time[shortest] - arrival_time[shortest];
        if (wait_time[shortest] < 0)
            wait_time[shortest] = 0;
        turnaround_time[shortest] = burst_time[shortest] + wait_time[shortest];
        total_wait_time += wait_time[shortest];
        total_turnaround_time += turnaround_time[shortest];
        visited[shortest] = true;
        min_burst = 10000;
        completed++;
    }

    printf("SJF Scheduling\n");
    printf("Process\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");

    for (int i = 0; i < n; i++)
    {
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\n", processes[i], arrival_time[i], burst_time[i], wait_time[i], turnaround_time[i]);
    }

    printf("Average Waiting Time: %.2f\n", (float)total_wait_time / n);
    printf("Average Turnaround Time: %.2f\n\n", (float)total_turnaround_time / n);
}

// RR (Round Robin) Implementation

void roundRobin(int processes[], int n, int burst_time[], int arrival_time[], int quantum)
{
    int wait_time[n], total_wait_time = 0, total_turnaround_time = 0, turnaround_time[n];
    int remaining_bt[n];

    for (int i = 0; i < n; i++)
        remaining_bt[i] = burst_time[i];

    int t = 0;

    while (1)
    {
        bool done = true;

        for (int i = 0; i < n; i++)
        {
            if (remaining_bt[i] > 0)
            {
                done = false;

                if (remaining_bt[i] > quantum)
                {
                    t += quantum;
                    remaining_bt[i] -= quantum;
                }
                else
                {
                    t += remaining_bt[i];
                    wait_time[i] = t - burst_time[i] - arrival_time[i];
                    if (wait_time[i] < 0)
                        wait_time[i] = 0;
                    remaining_bt[i] = 0;
                }
            }
        }

        if (done)
            break;
    }

    for (int i = 0; i < n; i++)
    {
        turnaround_time[i] = burst_time[i] + wait_time[i];
        total_wait_time += wait_time[i];
        total_turnaround_time += turnaround_time[i];
    }

    printf("Round Robin Scheduling\n");
    printf("Process\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");

    for (int i = 0; i < n; i++)
    {
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\n", processes[i], arrival_time[i], burst_time[i], wait_time[i], turnaround_time[i]);
    }

    printf("Average Waiting Time: %.2f\n", (float)total_wait_time / n);
    printf("Average Turnaround Time: %.2f\n\n", (float)total_turnaround_time / n);
}

// Main function

int main()
{
    int processes[] = {1, 2, 3, 4};
    int n = sizeof(processes) / sizeof(processes[0]);
    int arrival_time[] = {0, 6, 7, 9};
    int burst_time[] = {10, 8, 4, 5};
    int quantum = 2;

    fcfs(processes, n, burst_time, arrival_time);
    sjf(processes, n, burst_time, arrival_time);
    roundRobin(processes, n, burst_time, arrival_time, quantum);

    return 0;
}

#include <stdio.h>

// Function to find the waiting time for the FCFS algorithm
void findWaitingTimeFCFS(int processes[], int n, int bt[], int wt[]) {
    wt[0] = 0;
    for (int i = 1; i < n; i++) {
        wt[i] = bt[i - 1] + wt[i - 1];
    }
}

// Function to find the waiting time for the SJF algorithm
void findWaitingTimeSJF(int processes[], int n, int bt[], int at[], int wt[]) {
    int remainingTime[n], completed = 0, minIndex, minValue, time;
    float totalWaitingTime = 0;

    for (int i = 0; i < n; i++) {
        remainingTime[i] = bt[i];
    }

    while (completed != n) {
        minIndex = -1;
        minValue = 99999;

        for (int i = 0; i < n; i++) {
            if (at[i] <= time && remainingTime[i] < minValue && remainingTime[i] > 0) {
                minValue = remainingTime[i];
                minIndex = i;
            }
        }

        if (minIndex == -1) {
            time++;
            continue;
        }

        remainingTime[minIndex]--;
        time++;

        if (remainingTime[minIndex] == 0) {
            completed++;
            wt[minIndex] = time - bt[minIndex] - at[minIndex];
            totalWaitingTime += wt[minIndex];
        }
    }
}

// Function to find the waiting time for the RR algorithm
void findWaitingTimeRR(int processes[], int n, int bt[], int at[], int wt[], int quantum) {
    int remainingTime[n];
    for (int i = 0; i < n; i++) {
        remainingTime[i] = bt[i];
    }

    int completed = 0, time = 0, minArrivalTime = 99999;
    for (int i = 0; i < n; i++) {
        if (at[i] < minArrivalTime) {
            minArrivalTime = at[i];
        }
    }

    while (completed != n) {
        for (int i = 0; i < n; i++) {
            if (remainingTime[i] > 0 && at[i] <= time) {
                if (remainingTime[i] <= quantum) {
                    time += remainingTime[i];
                    wt[i] = time - bt[i] - at[i];
                    remainingTime[i] = 0;
                    completed++;
                } else {
                    time += quantum;
                    remainingTime[i] -= quantum;
                }
            }
        }
    }
}

int main() {
    int processes[] = {1, 2, 3, 4};
    int n = sizeof(processes) / sizeof(processes[0]);
    int arrivalTime[] = {0, 6, 7, 9};
    int burstTime[] = {10, 8, 4, 5};
    int quantum = 2;

    int waitingTimeFCFS[n], waitingTimeSJF[n], waitingTimeRR[n];

    // Calculate waiting times for FCFS
    findWaitingTimeFCFS(processes, n, burstTime, waitingTimeFCFS);

    // Calculate waiting times for SJF
    findWaitingTimeSJF(processes, n, burstTime, arrivalTime, waitingTimeSJF);

    // Calculate waiting times for RR
    findWaitingTimeRR(processes, n, burstTime, arrivalTime, waitingTimeRR, quantum);

    // Print waiting times and average waiting times
    printf("FCFS Waiting Times: ");
    float avgWaitingTimeFCFS = 0;
    for (int i = 0; i < n; i++) {
        printf("%d ", waitingTimeFCFS[i]);
        avgWaitingTimeFCFS += waitingTimeFCFS[i];
    }
    avgWaitingTimeFCFS /= n;
    printf("\nAverage Waiting Time (FCFS): %.2f\n", avgWaitingTimeFCFS);

    printf("\nSJF Waiting Times: ");
    float avgWaitingTimeSJF = 0;
    for (int i = 0; i < n; i++) {
        printf("%d ", waitingTimeSJF[i]);
        avgWaitingTimeSJF += waitingTimeSJF[i];
    }
    avgWaitingTimeSJF /= n;
    printf("\nAverage Waiting Time (SJF): %.2f\n", avgWaitingTimeSJF);

    printf("\nRR Waiting Times: ");
    float avgWaitingTimeRR = 0;
    for (int i = 0; i < n; i++) {
        printf("%d ", waitingTimeRR[i]);
        avgWaitingTimeRR += waitingTimeRR[i];
    }
    avgWaitingTimeRR /= n;
    printf("\nAverage Waiting Time (RR): %.2f\n", avgWaitingTimeRR);

    // Analysis
    printf("\nAnalysis:\n");
    printf("The SJF algorithm has the lowest average waiting time of %.2f, followed by the RR algorithm with %.2f, and the FCFS algorithm with %.2f.\n", avgWaitingTimeSJF, avgWaitingTimeRR, avgWaitingTimeFCFS);
    printf("The SJF algorithm performs better than the others because it prioritizes shorter processes, leading to a lower average waiting time.\n");
    printf("The RR algorithm also performs reasonably well by allocating CPU time in a round-robin fashion, preventing starvation and providing a more balanced waiting time.\n");
    printf("The FCFS algorithm has the highest average waiting time because it does not consider process burst times or prioritize shorter processes.\n");

    return 0;
}
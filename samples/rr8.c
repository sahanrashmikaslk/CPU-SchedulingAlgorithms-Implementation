#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

struct RR {
    int arrival;
    int burst;
    int start[20];
    int wait;
    int complete;
    int tat;
    int process;
};

int quantum; // Quantum for Round Robin scheduling

int main() {
    int n, i, j;

    // Taking Input
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    struct RR p[n];

    printf("Enter the quantum: \n");
    scanf("%d", &quantum);

    printf("Enter the process numbers: \n");
    for (i = 0; i < n; i++) {
        scanf("%d", &(p[i].process));
    }

    printf("Enter the Arrival time of processes: \n");
    for (i = 0; i < n; i++) {
        scanf("%d", &(p[i].arrival));
    }

    printf("Enter the Burst time of processes: \n");
    for (i = 0; i < n; i++) {
        scanf("%d", &(p[i].burst));
    }

    // Declaring variables
    int c = n, s[n][20];
    float time = 0, mini = INT_MAX, b[n], a[n];

    // Initializing burst and arrival time arrays
    int index = -1;
    for (i = 0; i < n; i++) {
        b[i] = p[i].burst;
        a[i] = p[i].arrival;
        for (j = 0; j < 20; j++) {
            s[i][j] = -1;
        }
    }

    int tot_wt = 0, tot_tat = 0;
    bool flag = false;

    while (c != 0) {
        mini = INT_MAX;
        flag = false;

        for (i = 0; i < n; i++) {
            float p_time = time + 0.1;
            if (a[i] <= p_time && mini > a[i] && b[i] > 0) {
                index = i;
                mini = a[i];
                flag = true;
            }
        }

        // If no process is ready, increment time
        if (!flag) {
            time++;
            continue;
        }

        // Calculating start time
        j = 0;
        while (s[index][j] != -1) {
            j++;
        }

        if (s[index][j] == -1) {
            s[index][j] = time;
            p[index].start[j] = time;
        }

        if (b[index] <= quantum) {
            time += b[index];
            b[index] = 0;
        } else {
            time += quantum;
            b[index] -= quantum;
        }

        if (b[index] > 0) {
            a[index] = time + 0.1;
        }

        // Calculating final times and wait times
        if (b[index] == 0) {
            c--;
            p[index].complete = time;
            p[index].wait = p[index].complete - p[index].arrival - p[index].burst;
            tot_wt += p[index].wait;
            p[index].tat = p[index].burst + p[index].wait;
            tot_tat += p[index].tat;
        }
    }

    // Printing output
    printf("Process number \tArrival time \tBurst time \tStart time \t\t\t\tFinal time \tWait Time \tTurnAround Time\n");

    for (i = 0; i < n; i++) {
        printf("%d \t\t%d \t\t%d \t\t", p[i].process, p[i].arrival, p[i].burst);
        j = 0;
        int v = 0;
        while (p[i].start[j] != -1) {
            printf("%d ", p[i].start[j]);
            j++;
            v += 3;
        }
        while (v < 40) {
            printf(" ");
            v++;
        }
        printf("\t%d \t\t%d \t\t%d\n", p[i].complete, p[i].wait, p[i].tat);
    }

    // Calculating average wait time and turnaround time
    double avg_wt = tot_wt / (float)n;
    double avg_tat = tot_tat / (float)n;

    // Printing average wait time and turnaround time
    printf("The average wait time is: %lf\n", avg_wt);
    printf("The average TurnAround time is: %lf\n", avg_tat);

    return 0;
}

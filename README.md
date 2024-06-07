# CPU Scheduling Algorithms Using C

This repository contains implementations of three CPU scheduling algorithms,
 - First-Come, First-Served (FCFS)
 - Shortest Job First (SJF)
 - Round Robin (RR)

These algorithms are compared based on their average waiting times for a set of processes.

## Introduction

The goal of this assignment is to implement and compare three different CPU scheduling algorithms. These algorithms are evaluated based on the average waiting time for a given set of processes.

## Algorithms

### First-Come, First-Served (FCFS)

FCFS is the simplest scheduling algorithm. Processes are scheduled in the order they arrive in the ready queue. While easy to implement, FCFS can lead to the "convoy effect" where shorter processes wait for a long process to complete.

### Shortest Job First (SJF)

SJF selects the process with the smallest burst time next. This typically results in lower average waiting times but requires accurate predictions of process burst times. SJF can lead to starvation of longer processes if shorter processes keep arriving.

### Round Robin (RR)

RR assigns a fixed time quantum to each process in a cyclic order, ensuring all processes get a fair share of CPU time. While fair, this can lead to higher waiting times due to frequent context switching.

## Process Data

The process data used for this comparison is as follows:

| Process | Arrival Time | Burst Time |
|---------|--------------|------------|
| P1      | 0            | 10         |
| P2      | 6            | 8          |
| P3      | 7            | 4          |
| P4      | 9            | 5          |

## Results

### Average Waiting Times

- **FCFS**: 7.00
- **SJF**: 5.25
- **RR (Quantum = 2)**: 10.50

### Analysis

- **SJF** offers the lowest average waiting time but requires knowing burst times in advance.
- **FCFS** is simple but can result in longer wait times if long processes arrive early.
- **RR** ensures fairness but can have higher waiting times due to context switching.

## How to Run

To compile and run the code for each scheduling algorithm, follow the instructions below.

1. **Clone the repository**:
    ```bash
    git clone https://github.com/sahanrashmikaslk/CPU-SchedulingAlgorithms-using-C.git
    cd CPU-SchedulingAlgorithms-using-C
    ```

2. **Compile and run FCFS**:
    ```bash
    gcc First-Come-FirstServe.c
    ./First-Come-FirstServe
    ```

3. **Compile and run SJF**:
    ```bash
    gcc Shortest-Job-First.c 
    ./Shortest-Job-First
    ```

4. **Compile and run RR**:
    ```bash
    gcc Round-Robin.c
    ./Round-Robin
    ```

## Conclusion

The choice of scheduling algorithm should be based on the specific requirements and constraints of the system. SJF offers the best performance in terms of minimizing average waiting time but requires accurate burst time predictions. FCFS is straightforward but less efficient with diverse process lengths. RR provides fairness and is suitable for time-sharing systems, though it may have higher average waiting times due to context switching overhead. Understanding these trade-offs is crucial for selecting the appropriate scheduling strategy for a given scenario.

---

Feel free to explore the code and compare the performance of these algorithms with different sets of process data. Contributions and improvements are welcome!


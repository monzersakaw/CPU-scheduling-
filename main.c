#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int process_id;
    int arrival_time;
    int burst_time;
    int priority;
} Process;

void mlfq(Process processes[], int num_processes);
void fcfs(Process processes[], int num_processes);
void sjf(Process processes[], int num_processes);
void priorityScheduling(Process processes[], int num_processes);
void roundRobin(Process processes[], int num_processes, int time_quantum);

int main() {
    Process processes[] = {
        {0, 0, 8, 1}, // Queue 0, Process 0, Burst time = 8, Priority = 1
        {1, 1, 4, 2},
        {2, 2, 9, 3},
        {3, 3, 5, 4},
        {4, 4, 2, 5}
    };


    int num_processes = sizeof(processes) / sizeof(Process);
    printf("num of processes: %d\n\n", num_processes);
    int time_quantum = 3;

    printf("\nMLFQ: \n\n");
    mlfq(processes, num_processes);

    printf("\nFCFS: \n\n");
    fcfs(processes, num_processes);

    printf("\nSJF: \n\n");
    sjf(processes, num_processes);

    printf("\nPriority Scheduling: \n\n");
    priorityScheduling(processes, num_processes);

    printf("\nRound Robin: \n\n");
    roundRobin(processes, num_processes, time_quantum);

    return 0;
}


void mlfq(Process processes[], int num_processes) {
    int total_execution_time = 0;
    int time_quantum_queue1 = 4;
    int time_quantum_queue2 = 8;

    // Queue 0 execution (highest priority)
    for (int i = 0; i < num_processes; i++) {
        int remaining_burst_time = processes[i].burst_time;

        if (remaining_burst_time <= time_quantum_queue1) {
            // Process can complete execution in Queue 0
            printf("Process %d executed for %d units in Queue 0\n", processes[i].process_id, remaining_burst_time);
            total_execution_time += remaining_burst_time;
        } else {
            // Process moves to Queue 1
            printf("Process %d executed for %d units in Queue 0\n", processes[i].process_id, time_quantum_queue1);
            total_execution_time += time_quantum_queue1;

            remaining_burst_time -= time_quantum_queue1;

            // Queue 1 execution
            if (remaining_burst_time <= time_quantum_queue2) {
                // Process can complete execution in Queue 1
                printf("Process %d executed for %d units in Queue 1\n", processes[i].process_id, remaining_burst_time);
                total_execution_time += remaining_burst_time;
            } else {
                // Process moves to Queue 2
                printf("Process %d executed for %d units in Queue 1\n", processes[i].process_id, time_quantum_queue2);
                total_execution_time += time_quantum_queue2;

                remaining_burst_time -= time_quantum_queue2;

                // Queue 2 execution
                printf("Process %d executed for %d units in Queue 2\n", processes[i].process_id, remaining_burst_time);
                total_execution_time += remaining_burst_time;
            }
        }
    }

    printf("Total execution time (MLFQ): %d\n", total_execution_time);
}




// Function to simulate FCFS scheduling
void fcfs(Process processes[], int num_processes) {
    int total_execution_time = 0;
    int current_time = 0;

    for (int i = 0; i < num_processes; i++) {
        if (current_time < processes[i].arrival_time) {
            current_time = processes[i].arrival_time;
        }

        printf("Process %d executed\n", processes[i].process_id);
        total_execution_time += current_time - processes[i].arrival_time + processes[i].burst_time;
        current_time += processes[i].burst_time;
    }

    printf("Total execution time (FCFS): %d\n", total_execution_time);
}

// Function to simulate SJF scheduling
void sjf(Process processes[], int num_processes) {
    int total_execution_time = 0;

    // Sort the processes based on burst time (shortest burst time first)
    for (int i = 0; i < num_processes - 1; i++) {
        for (int j = 0; j < num_processes - i - 1; j++) {
            if (processes[j].burst_time > processes[j + 1].burst_time) {
                // Swap processes
                Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }

    int current_time = 0;
    for (int i = 0; i < num_processes; i++) {
        if (current_time < processes[i].arrival_time) {
            current_time = processes[i].arrival_time;
        }

        printf("Process %d executed\n", processes[i].process_id);
        total_execution_time += current_time - processes[i].arrival_time + processes[i].burst_time;
        current_time += processes[i].burst_time;
    }

    printf("Total execution time (SJF): %d\n", total_execution_time);
}

// Function to simulate Priority Scheduling
void priorityScheduling(Process processes[], int num_processes) {
    int total_execution_time = 0;
    int current_time = 0;

    // Sort the processes based on priority (highest priority first)
    for (int i = 0; i < num_processes - 1; i++) {
        for (int j = 0; j < num_processes - i - 1; j++) {
            if (processes[j].priority < processes[j + 1].priority) {
                // Swap processes
                Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }

    for (int i = 0; i < num_processes; i++) {
        if (current_time < processes[i].arrival_time) {
            current_time = processes[i].arrival_time;
        }

        printf("Process %d executed\n", processes[i].process_id);
        total_execution_time += current_time - processes[i].arrival_time + processes[i].burst_time;
        current_time += processes[i].burst_time;
    }

    printf("Total execution time (Priority Scheduling): %d\n", total_execution_time);
}
// Function to simulate Round Robin scheduling
void roundRobin(Process processes[], int num_processes, int time_quantum) {
    int total_execution_time = 0;
    int remaining_burst_time[num_processes];
    bool is_completed[num_processes];

    for (int i = 0; i < num_processes; i++) {
        remaining_burst_time[i] = processes[i].burst_time;
        is_completed[i] = false;
    }

    int current_time = 0;
    while (true) {
        bool all_completed = true;

        for (int i = 0; i < num_processes; i++) {
            if (!is_completed[i]) {
                all_completed = false;

                if (remaining_burst_time[i] <= time_quantum) {
                    current_time += remaining_burst_time[i];
                    remaining_burst_time[i] = 0;
                    is_completed[i] = true;
                    printf("Process %d executed for %d units\n", processes[i].process_id, remaining_burst_time[i]);
                } else {
                    current_time += time_quantum;
                    remaining_burst_time[i] -= time_quantum;
                    printf("Process %d executed for %d units\n", processes[i].process_id, time_quantum);
                }
            }
        }

        if (all_completed) {
            break;
        }
    }

    printf("Total execution time (Round Robin): %d\n", current_time);
}

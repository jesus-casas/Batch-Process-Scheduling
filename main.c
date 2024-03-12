#include <stdio.h>
#include <stdlib.h>

// Structure to represent a process
typedef struct {
    int id;
    int arrival;
    int total_time;
    int total_remaining;
    int done;
    int start_time;
    int already_started;
    int end_time;
    int turnaround_time;
} Process;

// Global variables
Process *processes = NULL;
int total_processes = 0;

// Function declarations
void enter_parameters();
void schedule_fifo();
void schedule_sjf();
void schedule_srt();
void print_table();
void free_memory();

// Function to enter parameters for the processes and allocate memory
void enter_parameters() {
    printf("Enter the total number of processes: ");
    // checking input
    while (1)
    {
        scanf("%d", &total_processes);
        if (total_processes > 0)
        {
            break;
        }
        printf("Invalid input. Please enter a positive number: ");
    }
    processes = (Process *)malloc(total_processes * sizeof(Process));
    int process_count1 = 1;
    for (int i = 0; i < total_processes; i++)
    {
        processes[i].id = process_count1;
        printf("Enter arrival cycle for process %d: ", process_count1);
        scanf("%d", &processes[i].arrival);
        printf("Enter total cycles for process %d: ", process_count1);
        scanf("%d", &processes[i].total_time);
        process_count1++;
    }
    print_table();
}

// Function to reset the processes
void reset_processes() {
    for (int i = 0; i < total_processes; i++) {
        processes[i].done = 0; 
        processes[i].start_time = 0; 
        processes[i].end_time = 0; 
        processes[i].turnaround_time = 0; 
        processes[i].total_remaining = processes[i].total_time;
        processes[i].already_started = 0; 
    }
}

// Function to schedule processes with First In First Out (FIFO) algorithm
void schedule_fifo() {
    int current_time = 0;
    for (int i = 0; i < total_processes; i++)
    {
        if (current_time < processes[i].arrival)
        {
            current_time = processes[i].arrival;
        }
        processes[i].start_time = current_time;
        processes[i].end_time = current_time + processes[i].total_time;
        processes[i].turnaround_time = processes[i].end_time - processes[i].arrival;
        current_time = processes[i].end_time;
    }
    
}

// Function to schedule processes with Shortest Job First (SJF) algorithm
void schedule_sjf() {
    int current_time = 0;
    for (int i = 0; i < total_processes; i++)
    {
        if (current_time < processes[i].arrival)
        {
            current_time = processes[i].arrival;
        }
        int shortest_job = 1000000;
        int shortest_index = 0;
        for (int j = 0; j < total_processes; j++)
        {
            if (processes[j].arrival <= current_time && processes[j].done == 0)
            {
                if (processes[j].total_time < shortest_job)
                {
                    shortest_job = processes[j].total_time;
                    shortest_index = j;
                }
            }
        }
        processes[shortest_index].start_time = current_time;
        processes[shortest_index].end_time = current_time + processes[shortest_index].total_time;
        processes[shortest_index].turnaround_time = processes[shortest_index].end_time - processes[shortest_index].arrival;
        current_time = processes[shortest_index].end_time;
        processes[shortest_index].done = 1;
    }
}

// Function to schedule processes with Shortest Remaining Time (SRT) algorithm
void schedule_srt() {
    int current_time = 0;
    int completed_processes = 0;

    // Initialize total_remaining and already_started for each process
    for (int i = 0; i < total_processes; i++) {
        processes[i].total_remaining = processes[i].total_time;
        processes[i].already_started = 0;
    }

    // Loop until all processes are completed
    while (completed_processes != total_processes) {
        int shortest_job = 1000000; 
        int shortest_index = -1;

        // Find the process with the shortest remaining time
        for (int j = 0; j < total_processes; j++) {
            if (processes[j].arrival <= current_time && !processes[j].done && processes[j].total_remaining < shortest_job) {
                shortest_job = processes[j].total_remaining;
                shortest_index = j;
            }
        }

        // If no process is found, increment current_time and continue
        if (shortest_index == -1) {
            current_time++;
            continue;
        }

        // Update the start time for the selected process if it hasn't started yet
        if (!processes[shortest_index].already_started) {
            processes[shortest_index].start_time = current_time;
            processes[shortest_index].already_started = 1;
        }

        // Execute the process for one time unit
        processes[shortest_index].total_remaining--;
        current_time++;

        // Check if the process is completed
        if (processes[shortest_index].total_remaining == 0) {
            processes[shortest_index].end_time = current_time;
            processes[shortest_index].turnaround_time = processes[shortest_index].end_time - processes[shortest_index].arrival;
            processes[shortest_index].done = 1;
            completed_processes++;
        }

    }
}

// Function to print the table of processes
void print_table() {
    printf("PID\tArrival\tTotal \tStart\tEnd\tTurnaround\n");
    printf("----------------------------------------------------\n");
    for (int i = 0; i < total_processes; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", processes[i].id, processes[i].arrival, processes[i].total_time, processes[i].start_time, processes[i].end_time, processes[i].turnaround_time);
    }
}

// Function to free the memory allocated for the processes
void free_memory() {
    if (processes != NULL) {
        free(processes);
        processes = NULL;
    }
}

int main() {
    int choice;

    do {
        printf("Batch scheduling\n");
        printf("----------------\n");
        printf("1) Enter parameters\n");
        printf("2) Schedule processes with FIFO algorithm\n");
        printf("3) Schedule processes with SJF algorithm\n");
        printf("4) Schedule processes with SRT algorithm\n");
        printf("5) Quit and free memory\n");
        printf("Enter selection: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                enter_parameters();
                break;
            case 2:
                reset_processes();
                schedule_fifo();
                print_table();

                break;
            case 3:
                reset_processes();
                schedule_sjf();
                print_table();
                break;
            case 4:
                reset_processes();
                schedule_srt();
                print_table();
                break;
            case 5:
                free_memory();
                printf("Quitting program\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (choice != 5);

    return 0;
}
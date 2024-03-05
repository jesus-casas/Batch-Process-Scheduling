#include <stdio.h>
#include <stdlib.h>

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

Process *processes = NULL;
int total_processes = 0;

// Function declarations
void enter_parameters();
void schedule_fifo();
void schedule_sjf();
void schedule_srt();
void print_table();
void free_memory();


void enter_parameters() {
    // TODO: Implement this function to input the total number of processes
    // and the arrival and total CPU time for each process.
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

void schedule_fifo() {
    // TODO: Implement the FIFO scheduling algorithm.
    // Update start_time, end_time, and turnaround_time for each process.
}

void schedule_sjf() {
    // TODO: Implement the SJF scheduling algorithm.
    // Update start_time, end_time, and turnaround_time for each process.
}

void schedule_srt() {
    // TODO: Implement the SRT scheduling algorithm.
    // Update start_time, end_time, and turnaround_time for each process.
    // Remember to update total_remaining and already_started as needed.
}

void print_table() {
    // TODO: Implement this function to print the table of processes
    // with their timing parameters.
    printf("PID\tArrival\tTotal \tStart\tEnd\tTurnaround\n");
    printf("-------\t-------\t---------\t-----\t---\t----------\n");
    for (int i = 0; i < total_processes; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", processes[i].id, processes[i].arrival, processes[i].total_time, processes[i].start_time, processes[i].end_time, processes[i].turnaround_time);
    }
}

void free_memory() {
    // Free the dynamically allocated memory for processes.
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
                schedule_fifo();
                print_table();
                break;
            case 3:
                schedule_sjf();
                print_table();
                break;
            case 4:
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

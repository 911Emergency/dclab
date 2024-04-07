#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 10

// Process struct
typedef struct
{
    int id;
    bool active;
} Process;

// Global array to store processes
Process processes[MAX_PROCESSES];
int numProcesses;

// Function to initialize processes
void initializeProcesses(int num)
{
    numProcesses = num;
    for (int i = 0; i < numProcesses; i++)
    {
        processes[i].id = i + 1;
        processes[i].active = true;
    }
}

// Function to simulate election process
void startElection(int processId)
{
    printf("Process %d initiates an election.\n", processId);

    int maxId = processId;
    // Send election messages to higher priority processes
    for (int i = processId + 1; i <= numProcesses; i++)
    {
        if (processes[i - 1].active)
        {
            printf("Process %d sends election message to process %d.\n", processId, i);
            maxId = i;
        }
    }

    // Declare itself as coordinator if no response received
    if (maxId == processId)
    {
        printf("Process %d declares itself as coordinator.\n", processId);
        // Declare itself as coordinator
        // Broadcast coordinator message to all processes
        for (int i = 0; i < numProcesses; i++)
        {
            if (processes[i].active && processes[i].id != processId)
            {
                printf("Process %d sends coordinator message to process %d.\n", processId, processes[i].id);
            }
        }
    }
    else
    {
        // Wait for coordinator message from higher priority process
        printf("Process %d waits for coordinator message.\n", processId);
    }
}

// Function to simulate a process failure
void simulateFailure(int processId)
{
    processes[processId - 1].active = false;
    printf("Process %d fails.\n", processId);
}

int main()
{
    // Initialize processes
    initializeProcesses(5);

    // Simulate failure of a process
    int failedProcessId = 3;
    simulateFailure(failedProcessId);

    // Start election from the failed process
    startElection(failedProcessId);

    return 0;
}

#include <iostream>
#include <vector>

using namespace std;

// Define the number of processes and resources
const int NUM_PROCESSES = 5;
const int NUM_RESOURCES = 3;

// Available resources
int available[NUM_RESOURCES] = {10, 5, 7};

// Maximum demand of each process
int maximum[NUM_PROCESSES][NUM_RESOURCES] = {
    {7, 5, 3},
    {3, 2, 2},
    {9, 0, 2},
    {2, 2, 2},
    {4, 3, 3}
};

// Resources allocated to each process
int allocation[NUM_PROCESSES][NUM_RESOURCES] = {
    {0, 1, 0},
    {2, 0, 0},
    {3, 0, 2},
    {2, 1, 1},
    {0, 0, 2}
};

// Need matrix
int need[NUM_PROCESSES][NUM_RESOURCES];

// Function to calculate the need matrix
void calculateNeed() {
    for (int i = 0; i < NUM_PROCESSES; ++i) {
        for (int j = 0; j < NUM_RESOURCES; ++j) {
            need[i][j] = maximum[i][j] - allocation[i][j];
        }
    }
}

// Function to check if the system is in a safe state
bool isSafe(int process, int request[]) {
    // Temporary arrays to simulate resource allocation
    int temp_available[NUM_RESOURCES];
    int temp_allocation[NUM_PROCESSES][NUM_RESOURCES];

    // Initialize temporary arrays
    for (int i = 0; i < NUM_RESOURCES; ++i) {
        temp_available[i] = available[i] - request[i];
        temp_allocation[process][i] = allocation[process][i] + request[i];
    }

    // Calculate temporary need matrix
    int temp_need[NUM_PROCESSES][NUM_RESOURCES];
    for (int i = 0; i < NUM_PROCESSES; ++i) {
        for (int j = 0; j < NUM_RESOURCES; ++j) {
            temp_need[i][j] = maximum[i][j] - temp_allocation[i][j];
        }
    }

    // Check if the temporary state is safe
    bool finish[NUM_PROCESSES] = {false};
    int work[NUM_RESOURCES];
    for (int i = 0; i < NUM_RESOURCES; ++i) {
        work[i] = temp_available[i];
    }

    int count = 0;
    while (count < NUM_PROCESSES) {
        bool found = false;
        for (int i = 0; i < NUM_PROCESSES; ++i) {
            if (!finish[i]) {
                bool can_allocate = true;
                for (int j = 0; j < NUM_RESOURCES; ++j) {
                    if (temp_need[i][j] > work[j]) {
                        can_allocate = false;
                        break;
                    }
                }

                if (can_allocate) {
                    for (int j = 0; j < NUM_RESOURCES; ++j) {
                        work[j] += temp_allocation[i][j];
                    }
                    finish[i] = true;
                    found = true;
                    count++;
                }
            }
        }
        if (!found) {
            return false; // Unsafe state
        }
    }

    return true; // Safe state
}

// Function to request resources
bool requestResources(int process, int request[]) {
    for (int i = 0; i < NUM_RESOURCES; ++i) {
        if (request[i] > need[process][i] || request[i] > available[i]) {
            return false; // Invalid request
        }
    }

    // Try to simulate resource allocation
    for (int i = 0; i < NUM_RESOURCES; ++i) {
        available[i] -= request[i];
        allocation[process][i] += request[i];
        need[process][i] -= request[i];
    }

    // Check if the system is in a safe state
    if (isSafe(process, request)) {
        return true; // Resources allocated
    } else {
        // Rollback allocation if not safe
        for (int i = 0; i < NUM_RESOURCES; ++i) {
            available[i] += request[i];
            allocation[process][i] -= request[i];
            need[process][i] += request[i];
        }
        return false; // Allocation would lead to an unsafe state
    }
}

int main() {
    calculateNeed();

    // Example: Process 1 requests resources
    int process = 1;
    int request[NUM_RESOURCES] = {1, 0, 2};

    if (requestResources(process, request)) {
        cout << "Request granted. Allocation after request:" << endl;
        for (int i = 0; i < NUM_PROCESSES; ++i) {
            cout << "Process " << i << ": ";
            for (int j = 0; j < NUM_RESOURCES; ++j) {
                cout << allocation[i][j] << " ";
            }
            cout << endl;
        }
    } else {
        cout << "Request denied. System remains unchanged." << endl;
    }

    return 0;
}
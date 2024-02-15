#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

// Process structure
struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int remainingTime; // Remaining time to complete the process
};

// Function to perform Preemptive Shortest Job First scheduling
void PreemptiveSJF(vector<Process>& processes) {
    int n = processes.size();
    int currentTime = 0;

    while (true) {
        int shortestIndex = -1; // Index of the process with the shortest remaining burst time
        int shortestTime = INT_MAX; // Initialize to a large value

        // Find the process with the shortest remaining burst time
        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= currentTime && processes[i].remainingTime < shortestTime && processes[i].remainingTime > 0) {
                shortestIndex = i;
                shortestTime = processes[i].remainingTime;
            }
        }

        // If no process found, break the loop
        if (shortestIndex == -1) {
            break;
        }

        // Execute the process for a time quantum (e.g., 1 unit)
        processes[shortestIndex].remainingTime--;

        // Print process execution details
        cout << "Time " << currentTime << ": Process " << processes[shortestIndex].id << " is executing." << endl;

        // Update current time
        currentTime++;

        // Check if the process is completed
        if (processes[shortestIndex].remainingTime == 0) {
            cout << "Time " << currentTime << ": Process " << processes[shortestIndex].id << " completed." << endl;
        }
    }
}

int main() {
    vector<Process> processes;
    int n;

    cout << "Enter the number of processes: ";
    cin >> n;

    // Input process details
    for (int i = 0; i < n; i++) {
        Process p;
        p.id = i + 1;
        cout << "Enter arrival time for Process " << p.id << ": ";
        cin >> p.arrivalTime;
        cout << "Enter burst time for Process " << p.id << ": ";
        cin >> p.burstTime;
        p.remainingTime = p.burstTime;
        processes.push_back(p);
    }

    // Perform Preemptive SJF scheduling
    PreemptiveSJF(processes);

    return 0;
}
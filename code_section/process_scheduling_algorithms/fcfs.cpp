#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

// Process structure
struct Process {
    int id;
    int arrivalTime;
    int burstTime;
};

// Function to perform FCFS scheduling
void FCFS(vector<Process>& processes) {
    int n = processes.size();

    // Calculate completion time for each process
    int currentTime = 0;
    for (int i = 0; i < n; i++) {
        // If the process arrives after the current time, wait for it
        if (processes[i].arrivalTime > currentTime) {
            currentTime = processes[i].arrivalTime;
        }

        // Calculate completion time for the current process
        currentTime += processes[i].burstTime;

        // Print completion time for the process
        cout << "Process " << processes[i].id << ": " << currentTime << endl;
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
        processes.push_back(p);
    }

    // Sort processes based on arrival time (if not already sorted)
    // This step is crucial for FCFS scheduling.
    sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.arrivalTime < b.arrivalTime;
    });

    // Perform FCFS scheduling
    FCFS(processes);

    return 0;
}
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Process structure
struct Process {
    int id;
    int priority;
    int burstTime;
};

// Function to perform Non-Preemptive Priority Scheduling
void NonPreemptivePriority(vector<Process>& processes) {
    int n = processes.size();

    // Sort processes by their priority (higher priority first)
    sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.priority > b.priority;
    });

    int currentTime = 0;
    vector<int> completionTime(n);

    for (int i = 0; i < n; i++) {
        // Calculate completion time for each process
        completionTime[i] = currentTime + processes[i].burstTime;
        currentTime = completionTime[i];

        // Print completion time for the process
        cout << "Process " << processes[i].id << ": " << completionTime[i] << endl;
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
        cout << "Enter priority for Process " << p.id << ": ";
        cin >> p.priority;
        cout << "Enter burst time for Process " << p.id << ": ";
        cin >> p.burstTime;
        processes.push_back(p);
    }

    // Perform Non-Preemptive Priority Scheduling
    NonPreemptivePriority(processes);

    return 0;
}
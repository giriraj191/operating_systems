#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

// Process structure
struct Process {
    int id;
    int arrivalTime;
    int priority;
    int burstTime;
    int remainingTime; // Remaining time to complete the process
};

// Function to perform Preemptive Priority Scheduling
void PreemptivePriority(vector<Process>& processes) {
    int n = processes.size();
    int currentTime = 0;

    // Create a priority queue (min-heap) to store processes based on priority
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    // Vector to track completion time for each process
    vector<int> completionTime(n);

    int completedProcesses = 0;

    while (completedProcesses < n) {
        // Push processes that have arrived into the priority queue
        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= currentTime && processes[i].remainingTime > 0) {
                pq.push({processes[i].priority, i});
            }
        }

        if (!pq.empty()) {
            // Get the process with the highest priority
            int index = pq.top().second;
            pq.pop();

            // Execute the process for a unit of time
            processes[index].remainingTime--;

            // Print process execution details
            cout << "Time " << currentTime << ": Process " << processes[index].id << " is executing." << endl;

            // Update current time
            currentTime++;

            // Check if the process is completed
            if (processes[index].remainingTime == 0) {
                completionTime[index] = currentTime;
                cout << "Time " << currentTime << ": Process " << processes[index].id << " completed." << endl;
                completedProcesses++;
            }
        } else {
            // If no processes are ready, simply increment the current time
            currentTime++;
        }
    }

    // Print completion times
    for (int i = 0; i < n; i++) {
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
        cout << "Enter arrival time for Process " << p.id << ": ";
        cin >> p.arrivalTime;
        cout << "Enter priority for Process " << p.id << ": ";
        cin >> p.priority;
        cout << "Enter burst time for Process " << p.id << ": ";
        cin >> p.burstTime;
        p.remainingTime = p.burstTime;
        processes.push_back(p);
    }

    // Perform Preemptive Priority Scheduling
    PreemptivePriority(processes);

    return 0;
}
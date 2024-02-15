#include <iostream>
#include <queue>

using namespace std;

// Process structure
struct Process {
    int id;
    int burstTime;
    int remainingTime; // Remaining time to complete the process
};

// Function to perform Round Robin scheduling
void RoundRobin(vector<Process>& processes, int quantum) {
    queue<Process> processQueue; // Queue to store processes

    int n = processes.size();
    int currentTime = 0; // Current time

    while (!processes.empty()) {
        Process currentProcess = processes.front();
        processes.erase(processes.begin());

        // Execute the process for the quantum time or until it completes
        int executeTime = min(quantum, currentProcess.remainingTime);
        currentProcess.remainingTime -= executeTime;
        currentTime += executeTime;

        // Print process execution details
        cout << "Process " << currentProcess.id << " executed for " << executeTime << " units of time." << endl;

        // Check if the process is completed
        if (currentProcess.remainingTime > 0) {
            // If not completed, push it back into the queue
            processQueue.push(currentProcess);
        } else {
            cout << "Process " << currentProcess.id << " completed at time " << currentTime << "." << endl;
        }

        // Check for other processes that have arrived
        while (!processes.empty() && processes.front().burstTime <= currentTime) {
            processQueue.push(processes.front());
            processes.erase(processes.begin());
        }

        // If the queue is not empty, push the current process back into the queue
        if (!processQueue.empty()) {
            processQueue.push(currentProcess);
        }
    }
}

int main() {
    vector<Process> processes;
    int n, quantum;

    cout << "Enter the number of processes: ";
    cin >> n;
    cout << "Enter the time quantum: ";
    cin >> quantum;

    // Input process details
    for (int i = 0; i < n; i++) {
        Process p;
        p.id = i + 1;
        cout << "Enter burst time for Process " << p.id << ": ";
        cin >> p.burstTime;
        p.remainingTime = p.burstTime;
        processes.push_back(p);
    }

    // Perform Round Robin scheduling
    RoundRobin(processes, quantum);

    return 0;
}
#include <iostream>
#include <thread>
#include <mutex>
#include <Windows.h>

using namespace std;

const int NUM_PHILOSOPHERS = 5;

HANDLE forks[NUM_PHILOSOPHERS];
HANDLE philoThreads[NUM_PHILOSOPHERS];

DWORD WINAPI philosopher(LPVOID param) {
    int id = (int)param;
    int left_fork = id;
    int right_fork = (id + 1) % NUM_PHILOSOPHERS;

    while (true) {
        // Think for a while
        cout << "Philosopher " << id << " is thinking." << endl;
        Sleep(1000);

        // Pick up the left fork
        WaitForSingleObject(forks[left_fork], INFINITE);
        cout << "Philosopher " << id << " picked up fork " << left_fork << " (left)." << endl;

        // Pick up the right fork
        WaitForSingleObject(forks[right_fork], INFINITE);
        cout << "Philosopher " << id << " picked up fork " << right_fork << " (right) and is eating." << endl;

        // Simulate eating
        Sleep(1000);

        // Release both forks
        ReleaseMutex(forks[left_fork]);
        ReleaseMutex(forks[right_fork]);

        // Think again before repeating
        cout << "Philosopher " << id << " finished eating and put down both forks." << endl;
        Sleep(1000);
    }

    return 0;
}

int main() {
    // Initialize forks (mutexes)
    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        forks[i] = CreateMutex(NULL, FALSE, NULL);
    }

    // Create philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        philoThreads[i] = CreateThread(NULL, 0, philosopher, (LPVOID)i, 0, NULL);
    }

    // Wait for philosopher threads to finish
    WaitForMultipleObjects(NUM_PHILOSOPHERS, philoThreads, TRUE, INFINITE);

    // Close handles
    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        CloseHandle(forks[i]);
        CloseHandle(philoThreads[i]);
    }

    return 0;
}

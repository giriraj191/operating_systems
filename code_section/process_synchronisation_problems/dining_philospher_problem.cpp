#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

const int NUM_PHILOSOPHERS = 5;

mutex forks[NUM_PHILOSOPHERS];
condition_variable cv[NUM_PHILOSOPHERS];

void philosopher(int id) {
    int left_fork = id;
    int right_fork = (id + 1) % NUM_PHILOSOPHERS;

    // To avoid deadlock, always pick up the smaller fork first
    if (left_fork > right_fork) {
        swap(left_fork, right_fork);
    }

    while (true) {
        // Think for a while
        cout << "Philosopher " << id << " is thinking." << endl;
        this_thread::sleep_for(chrono::milliseconds(1000));

        // Pick up the left fork
        unique_lock<mutex> left_lock(forks[left_fork]);
        cout << "Philosopher " << id << " picked up fork " << left_fork << " (left)." << endl;

        // Try to pick up the right fork
        unique_lock<mutex> right_lock(forks[right_fork], defer_lock);
        if (right_lock.try_lock()) {
            // Successfully picked up both forks, eat
            cout << "Philosopher " << id << " picked up fork " << right_fork << " (right) and is eating." << endl;
            this_thread::sleep_for(chrono::milliseconds(1000));
            cout << "Philosopher " << id << " finished eating and put down both forks." << endl;
            right_lock.unlock();
        } else {
            // Failed to pick up the right fork, release the left fork
            cout << "Philosopher " << id << " couldn't pick up fork " << right_fork << " (right) and put down fork " << left_fork << " (left)." << endl;
        }

        left_lock.unlock();

        // Wait for a while before repeating
        this_thread::sleep_for(chrono::milliseconds(1000));
    }
}

int main() {
    thread philosophers[NUM_PHILOSOPHERS];

    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        philosophers[i] = thread(philosopher, i);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        philosophers[i].join();
    }

    return 0;
}

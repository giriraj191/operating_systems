#include <iostream>
#include <thread>
#include <vector>
#include <queue>
#include <mutex>
#include <condition_variable>

using namespace std;

const int BUFFER_SIZE = 5; // Size of the shared buffer
const int NUM_PRODUCERS = 2; // Number of producer threads
const int NUM_CONSUMERS = 3; // Number of consumer threads
const int NUM_ITEMS = 10; // Total number of items to produce

queue<int> buffer; // Shared buffer
mutex mtx; // Mutex for protecting shared data
condition_variable buffer_not_full, buffer_not_empty; // Condition variables

void producer(int id) {
    for (int i = 0; i < NUM_ITEMS; ++i) {
        unique_lock<mutex> lock(mtx);

        // Wait until the buffer is not full
        buffer_not_full.wait(lock, [] { return buffer.size() < BUFFER_SIZE; });

        // Produce an item and add it to the buffer
        int item = i + (id * NUM_ITEMS); // Unique item for each producer
        buffer.push(item);
        cout << "Producer " << id << " produced item " << item << endl;

        // Signal that the buffer is not empty
        buffer_not_empty.notify_all();

        lock.unlock();

        // Simulate some work
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}

void consumer(int id) {
    for (int i = 0; i < NUM_ITEMS / NUM_CONSUMERS; ++i) {
        unique_lock<mutex> lock(mtx);

        // Wait until the buffer is not empty
        buffer_not_empty.wait(lock, [] { return !buffer.empty(); });

        // Consume an item from the buffer
        int item = buffer.front();
        buffer.pop();
        cout << "Consumer " << id << " consumed item " << item << endl;

        // Signal that the buffer is not full
        buffer_not_full.notify_all();

        lock.unlock();

        // Simulate some work
        this_thread::sleep_for(chrono::milliseconds(200));
    }
}

int main() {
    vector<thread> producerThreads(NUM_PRODUCERS);
    vector<thread> consumerThreads(NUM_CONSUMERS);

    for (int i = 0; i < NUM_PRODUCERS; ++i) {
        producerThreads[i] = thread(producer, i);
    }

    for (int i = 0; i < NUM_CONSUMERS; ++i) {
        consumerThreads[i] = thread(consumer, i);
    }

    for (int i = 0; i < NUM_PRODUCERS; ++i) {
        producerThreads[i].join();
    }

    for (int i = 0; i < NUM_CONSUMERS; ++i) {
        consumerThreads[i].join();
    }

    return 0;
}

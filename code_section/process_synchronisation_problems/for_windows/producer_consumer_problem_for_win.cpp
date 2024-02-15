#include <iostream>
#include <vector>
#include <queue>
#include <Windows.h>

using namespace std;

const int BUFFER_SIZE = 5; // Size of the shared buffer
const int NUM_PRODUCERS = 2; // Number of producer threads
const int NUM_CONSUMERS = 3; // Number of consumer threads
const int NUM_ITEMS = 10; // Total number of items to produce

queue<int> buffer; // Shared buffer
HANDLE mtx; // Mutex for protecting shared data
HANDLE buffer_not_full, buffer_not_empty; // Semaphores

void producer(int id) {
    for (int i = 0; i < NUM_ITEMS; ++i) {
        WaitForSingleObject(buffer_not_full, INFINITE);
        WaitForSingleObject(mtx, INFINITE);

        // Produce an item and add it to the buffer
        int item = i + (id * NUM_ITEMS); // Unique item for each producer
        buffer.push(item);
        cout << "Producer " << id << " produced item " << item << endl;

        ReleaseSemaphore(buffer_not_empty, 1, NULL);
        ReleaseMutex(mtx);

        // Simulate some work
        Sleep(100);
    }
}

void consumer(int id) {
    for (int i = 0; i < NUM_ITEMS / NUM_CONSUMERS; ++i) {
        WaitForSingleObject(buffer_not_empty, INFINITE);
        WaitForSingleObject(mtx, INFINITE);

        // Consume an item from the buffer
        int item = buffer.front();
        buffer.pop();
        cout << "Consumer " << id << " consumed item " << item << endl;

        ReleaseSemaphore(buffer_not_full, 1, NULL);
        ReleaseMutex(mtx);

        // Simulate some work
        Sleep(200);
    }
}

int main() {
    mtx = CreateMutex(NULL, FALSE, NULL);
    buffer_not_full = CreateSemaphore(NULL, BUFFER_SIZE, BUFFER_SIZE, NULL);
    buffer_not_empty = CreateSemaphore(NULL, 0, BUFFER_SIZE, NULL);

    vector<HANDLE> producerThreads(NUM_PRODUCERS);
    vector<HANDLE> consumerThreads(NUM_CONSUMERS);

    for (int i = 0; i < NUM_PRODUCERS; ++i) {
        producerThreads[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)producer, (LPVOID)i, 0, NULL);
    }

    for (int i = 0; i < NUM_CONSUMERS; ++i) {
        consumerThreads[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)consumer, (LPVOID)i, 0, NULL);
    }

    WaitForMultipleObjects(NUM_PRODUCERS, producerThreads.data(), TRUE, INFINITE);
    WaitForMultipleObjects(NUM_CONSUMERS, consumerThreads.data(), TRUE, INFINITE);

    CloseHandle(mtx);
    CloseHandle(buffer_not_full);
    CloseHandle(buffer_not_empty);

    return 0;
}

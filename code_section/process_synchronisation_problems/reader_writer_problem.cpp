#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <vector>

using namespace std;

const int NUM_READERS = 5;
const int NUM_WRITERS = 2;

mutex mtx; // Mutex for protecting shared data
condition_variable read_cv, write_cv; // Condition variables for readers and writers
int readers = 0; // Number of active readers

void reader(int id) {
    unique_lock<mutex> lock(mtx);
    cout << "Reader " << id << " is trying to read." << endl;
    
    // Wait for the writer to finish writing
    while (readers == -1) {
        read_cv.wait(lock);
    }

    // Reader can read now
    readers++;
    
    lock.unlock();

    // Simulate reading
    this_thread::sleep_for(chrono::milliseconds(100));
    
    lock.lock();
    cout << "Reader " << id << " finished reading." << endl;
    readers--;
    
    // If no readers are active, signal a waiting writer to write
    if (readers == 0) {
        write_cv.notify_one();
    }
}

void writer(int id) {
    unique_lock<mutex> lock(mtx);
    cout << "Writer " << id << " is trying to write." << endl;

    // Wait for all readers to finish reading
    while (readers != 0) {
        write_cv.wait(lock);
    }

    // Writer can write now
    readers = -1;
    
    lock.unlock();

    // Simulate writing
    this_thread::sleep_for(chrono::milliseconds(200));
    
    lock.lock();
    cout << "Writer " << id << " finished writing." << endl;
    
    // Reset readers and signal waiting readers
    readers = 0;
    read_cv.notify_all();
    write_cv.notify_one();
}

int main() {
    vector<thread> readerThreads;
    vector<thread> writerThreads;

    for (int i = 0; i < NUM_READERS; ++i) {
        readerThreads.emplace_back(reader, i);
    }

    for (int i = 0; i < NUM_WRITERS; ++i) {
        writerThreads.emplace_back(writer, i);
    }

    for (auto& readerThread : readerThreads) {
        readerThread.join();
    }

    for (auto& writerThread : writerThreads) {
        writerThread.join();
    }

    return 0;
}

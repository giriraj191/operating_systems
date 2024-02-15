#include <iostream>
#include <vector>
#include <Windows.h>

using namespace std;

const int NUM_READERS = 5;
const int NUM_WRITERS = 2;

HANDLE mtx; // Mutex for protecting shared data
HANDLE readSemaphore, writeSemaphore; // Semaphores for readers and writers
long readers = 0; // Number of active readers

void reader(int id) {
    cout << "Reader " << id << " is trying to read." << endl;

    WaitForSingleObject(readSemaphore, INFINITE);

    InterlockedIncrement(&readers);
    if (readers == 1) {
        WaitForSingleObject(writeSemaphore, INFINITE);
    }

    ReleaseSemaphore(readSemaphore, 1, NULL);

    // Simulate reading
    Sleep(100);

    WaitForSingleObject(readSemaphore, INFINITE);

    InterlockedDecrement(&readers);
    if (readers == 0) {
        ReleaseSemaphore(writeSemaphore, 1, NULL);
    }

    ReleaseSemaphore(readSemaphore, 1, NULL);

    cout << "Reader " << id << " finished reading." << endl;
}

void writer(int id) {
    cout << "Writer " << id << " is trying to write." << endl;

    WaitForSingleObject(writeSemaphore, INFINITE);

    // Simulate writing
    Sleep(200);

    ReleaseSemaphore(writeSemaphore, 1, NULL);

    cout << "Writer " << id << " finished writing." << endl;
}

int main() {
    mtx = CreateMutex(NULL, FALSE, NULL);
    readSemaphore = CreateSemaphore(NULL, 1, 1, NULL);
    writeSemaphore = CreateSemaphore(NULL, 1, 1, NULL);

    vector<HANDLE> readerThreads(NUM_READERS);
    vector<HANDLE> writerThreads(NUM_WRITERS);

    for (int i = 0; i < NUM_READERS; ++i) {
        readerThreads[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)reader, (LPVOID)i, 0, NULL);
    }

    for (int i = 0; i < NUM_WRITERS; ++i) {
        writerThreads[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)writer, (LPVOID)i, 0, NULL);
    }

    WaitForMultipleObjects(NUM_READERS, readerThreads.data(), TRUE, INFINITE);
    WaitForMultipleObjects(NUM_WRITERS, writerThreads.data(), TRUE, INFINITE);

    CloseHandle(mtx);
    CloseHandle(readSemaphore);
    CloseHandle(writeSemaphore);

    return 0;
}

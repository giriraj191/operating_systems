#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int main() {
    int head, n;
    cout << "Enter the current head position: ";
    cin >> head;
    cout << "Enter the number of disk requests: ";
    cin >> n;

    vector<int> requests(n);
    cout << "Enter the disk request queue: ";
    for (int i = 0; i < n; i++) {
        cin >> requests[i];
    }

    int totalSeekTime = 0;

    for (int i = 0; i < n; i++) {
        totalSeekTime += abs(head - requests[i]);
        head = requests[i];
    }

    cout << "Total seek time using FCFS: " << totalSeekTime << endl;

    return 0;
}
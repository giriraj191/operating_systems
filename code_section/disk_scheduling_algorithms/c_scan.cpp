#include <iostream>
#include <vector>
#include <algorithm>

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

    sort(requests.begin(), requests.end());

    int totalSeekTime = 0;

    // Find the index where the head is positioned
    int index = 0;
    for (int i = 0; i < n; i++) {
        if (requests[i] >= head) {
            index = i;
            break;
        }
    }

    // Forward pass
    for (int i = index; i < n; i++) {
        totalSeekTime += abs(head - requests[i]);
        head = requests[i];
    }

    // Wrap around
    totalSeekTime += abs(head - requests[n - 1]);
    head = 0;

    // Backward pass
    for (int i = 0; i < index; i++) {
        totalSeekTime += abs(head - requests[i]);
        head = requests[i];
    }

    cout << "Total seek time using C-SCAN: " << totalSeekTime << endl;

    return 0;
}
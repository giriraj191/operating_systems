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
    int startIndex = 0;
    int endIndex = 0;

    for (int i = 0; i < n; i++) {
        if (requests[i] >= head) {
            endIndex = i;
            break;
        }
    }

    for (int i = endIndex; i < n; i++) {
        totalSeekTime += abs(head - requests[i]);
        head = requests[i];
    }

    totalSeekTime += abs(head - requests[endIndex - 1]);
    head = requests[endIndex - 1];

    for (int i = endIndex - 1; i >= 0; i--) {
        totalSeekTime += abs(head - requests[i]);
        head = requests[i];
    }

    cout << "Total seek time using SCAN: " << totalSeekTime << endl;

    return 0;
}
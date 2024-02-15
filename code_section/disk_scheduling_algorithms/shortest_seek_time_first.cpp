#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <climits>

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

    while (!requests.empty()) {
        int minSeek = INT_MAX;
        int index = -1;

        for (int i = 0; i < requests.size(); i++) {
            int seek = abs(head - requests[i]);
            if (seek < minSeek) {
                minSeek = seek;
                index = i;
            }
        }

        totalSeekTime += minSeek;
        head = requests[index];
        requests.erase(requests.begin() + index);
    }

    cout << "Total seek time using SSTF: " << totalSeekTime << endl;

    return 0;
}
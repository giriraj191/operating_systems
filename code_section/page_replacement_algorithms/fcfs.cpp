#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>

using namespace std;

const int PAGE_FRAME_COUNT = 3; // Number of page frames in memory

// Function to display the contents of a vector
void displayVector(const vector<int>& v) {
    for (int val : v) {
        cout << val << " ";
    }
    cout << endl;
}

int main() {
    vector<int> pageReferences = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};

    queue<int> pageFrames; // Represents the page frames in memory
    unordered_set<int> pageSet; // Helps in checking if a page is already in memory

    vector<int> pageFaults; // Store page faults for each reference

    for (int page : pageReferences) {
        if (pageSet.count(page) == 0) {
            // Page fault: page is not in memory
            if (pageFrames.size() < PAGE_FRAME_COUNT) {
                // If there's room in memory, just add the page
                pageFrames.push(page);
                pageSet.insert(page);
            } else {
                // If memory is full, remove the oldest page (FCFS)
                int oldestPage = pageFrames.front();
                pageFrames.pop();
                pageSet.erase(oldestPage);

                // Add the new page
                pageFrames.push(page);
                pageSet.insert(page);
            }
            pageFaults.push_back(page);
        } else {
            // Page hit: page is already in memory
            pageFaults.push_back(-1); // -1 indicates a page hit
        }
    }

    // Display the page faults for each reference
    cout << "Page Faults: ";
    displayVector(pageFaults);

    return 0;
}
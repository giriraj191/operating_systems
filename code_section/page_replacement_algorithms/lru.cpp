#include <iostream>
#include <list>
#include <unordered_map>

using namespace std;

const int PAGE_FRAME_COUNT = 3; // Number of page frames in memory

// Function to display the contents of a list
void displayList(const list<int>& l) {
    for (int val : l) {
        cout << val << " ";
    }
    cout << endl;
}

int main() {
    list<int> pageFrames; // Represents the page frames in memory
    unordered_map<int, list<int>::iterator> pageMap; // Maps page numbers to list iterators

    list<int> pageReferences = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};

    list<int> pageFaults; // Store page faults for each reference

    for (int page : pageReferences) {
        // Check if the page is already in memory
        if (pageMap.find(page) != pageMap.end()) {
            // Page hit: Move the accessed page to the front of the list
            pageFrames.erase(pageMap[page]);
            pageFrames.push_front(page);
            pageMap[page] = pageFrames.begin();
            pageFaults.push_back(-1); // Page hit
        } else {
            // Page fault: Replace the least recently used page
            if (pageFrames.size() == PAGE_FRAME_COUNT) {
                int lruPage = pageFrames.back();
                pageFrames.pop_back();
                pageMap.erase(lruPage);
            }

            pageFrames.push_front(page);
            pageMap[page] = pageFrames.begin();
            pageFaults.push_back(page);
        }
    }

    // Display the page faults for each reference
    cout << "Page Faults: ";
    displayList(pageFaults);

    return 0;
}
#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <set>

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
    vector<int> pageFrames(PAGE_FRAME_COUNT, -1); // Represents the page frames in memory
    unordered_map<int, int> pageMap; // Maps page numbers to their access counts
    multiset<pair<int, int>> accessCounts; // Multiset to keep track of access counts and page numbers

    vector<int> pageReferences = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};

    vector<int> pageFaults; // Store page faults for each reference

    for (int page : pageReferences) {
        // Check if the page is already in memory
        if (pageMap.find(page) != pageMap.end()) {
            pageMap[page]++; // Increment the access count
            pageFaults.push_back(-1); // Page hit
        } else {
            // Page fault: Replace a page with the least access count
            if (pageFrames.size() == PAGE_FRAME_COUNT) {
                auto leastFrequent = accessCounts.begin();
                int pageToReplace = leastFrequent->second;

                int replacedPage = pageFrames[pageToReplace];
                pageFrames[pageToReplace] = page;
                pageMap.erase(replacedPage);
                accessCounts.erase(leastFrequent);
            } else {
                pageFrames.push_back(page);
            }

            pageMap[page] = 1; // Set the access count to 1 for the new page
            accessCounts.insert({1, page});
            pageFaults.push_back(page);
        }
    }

    // Display the page faults for each reference
    cout << "Page Faults: ";
    displayVector(pageFaults);

    return 0;
}
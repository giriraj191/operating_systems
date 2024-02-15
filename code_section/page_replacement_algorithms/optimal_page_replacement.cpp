#include<bits/stdc++.h>
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

    vector<int> pageFrames(PAGE_FRAME_COUNT, -1); // Represents the page frames in memory
    unordered_map<int, int> nextPageUse; // Stores the next use index for each page

    vector<int> pageFaults; // Store page faults for each reference

    for (int i = 0; i < pageReferences.size(); ++i) {
        int page = pageReferences[i];
        if (nextPageUse.find(page) == nextPageUse.end()) {
            // Page is not in the next use map; set its next use index
            for (int j = i + 1; j < pageReferences.size(); ++j) {
                if (pageReferences[j] == page) {
                    nextPageUse[page] = j;
                    break;
                }
                // If not found in future references, set to a large value
                nextPageUse[page] = numeric_limits<int>::max();
            }
        }

        if (pageFrames[i % PAGE_FRAME_COUNT] == -1) {
            // If there is an empty frame, just add the page
            pageFrames[i % PAGE_FRAME_COUNT] = page;
            pageFaults.push_back(page);
        } else {
            // Check if the page is already in memory
            if (find(pageFrames.begin(), pageFrames.end(), page) != pageFrames.end()) {
                pageFaults.push_back(-1); // Page hit
            } else {
                // Page fault: Replace the page with the longest next use
                int longestNextUse = -1;
                int pageToReplace = -1;
                for (int j = 0; j < PAGE_FRAME_COUNT; ++j) {
                    if (nextPageUse[pageFrames[j]] > longestNextUse) {
                        longestNextUse = nextPageUse[pageFrames[j]];
                        pageToReplace = j;
                    }
                }

                pageFrames[pageToReplace] = page;
                pageFaults.push_back(page);
            }
        }
    }

    // Display the page faults for each reference
    cout << "Page Faults: ";
    displayVector(pageFaults);

    return 0;
}
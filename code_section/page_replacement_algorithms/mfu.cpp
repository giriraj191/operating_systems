#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

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
    unordered_map<int, int> pageMap; // Maps page numbers to their access frequencies

    vector<int> pageReferences = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};

    vector<int> pageFaults; // Store page faults for each reference

    for (int page : pageReferences) {
        // Check if the page is already in memory
        if (pageMap.find(page) != pageMap.end()) {
            pageMap[page]++; // Increment the access frequency
            pageFaults.push_back(-1); // Page hit
        } else {
            // Page fault: Replace a page with the highest access frequency
            if (pageFrames.size() == PAGE_FRAME_COUNT) {
                int maxFrequency = -1;
                int pageToReplace = -1;

                for (int i = 0; i < PAGE_FRAME_COUNT; ++i) {
                    int framePage = pageFrames[i];
                    if (pageMap[framePage] > maxFrequency) {
                        maxFrequency = pageMap[framePage];
                        pageToReplace = i;
                    }
                }

                int replacedPage = pageFrames[pageToReplace];
                pageFrames[pageToReplace] = page;
                pageMap.erase(replacedPage);
            } else {
                pageFrames.push_back(page);
            }

            pageMap[page] = 1; // Set the access frequency to 1 for the new page
            pageFaults.push_back(page);
        }
    }

    // Display the page faults for each reference
    cout << "Page Faults: ";
    displayVector(pageFaults);

    return 0;
}
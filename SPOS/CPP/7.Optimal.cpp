#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

int findOptimalPage(const vector<int>& pageRequests, const unordered_set<int>& pageSet, int index) {
    int farthest = -1;
    int pageToReplace = -1;

    for (int page : pageSet) {
        int j = index;
        while (j < pageRequests.size()) {
            if (pageRequests[j] == page) {
                if (j > farthest) {
                    farthest = j;
                    pageToReplace = page;
                }
                break;
            }
            j++;
        }

        if (j == pageRequests.size()) {
            return page;
        }
    }

    return pageToReplace;
}

void simulateOptimalPageReplacement(const vector<int>& pageRequests, int frameCount) {
    unordered_set<int> pageSet;
    int pageFaults = 0;
    int pageHits = 0;

    cout << "+-----+--------------+----------------+----------------+" << endl;
    cout << "| Seq | Page Request | Page Frames     | Page Faults    |" << endl;
    cout << "+-----+--------------+----------------+----------------+" << endl;

    for (int i = 0; i < pageRequests.size(); i++) {
        int page = pageRequests[i];
        cout << "|  " << i + 1 << "  |      " << page << "       |";

        if (pageSet.find(page) == pageSet.end()) {
            if (pageSet.size() == frameCount) {
                int pageToReplace = findOptimalPage(pageRequests, pageSet, i + 1);
                pageSet.erase(pageToReplace);
            }
            pageSet.insert(page);
            pageFaults++;
            
            for (int frame : pageSet) {
                cout << "       " << frame;
            }
            
            for (int j = pageSet.size(); j < frameCount; j++) {
                cout << "                ";
            }

            cout << "| Page fault (F: " << pageFaults << ") |" << endl;
        } else {
            pageHits++;
            
            for (int frame : pageSet) {
                cout << "       " << frame;
            }
            
            for (int j = pageSet.size(); j < frameCount; j++) {
                cout << "                ";
            }

            cout << "| Page hit (H: " << pageHits << ")   |" << endl;
        }
    }

    cout << "+-----+--------------+----------------+----------------+" << endl;
    cout << "| Total Page Faults: " << pageFaults;
    for (int j = to_string(pageFaults).length(); j < 8; j++) {
        cout << " ";
    }
    cout << " |" << endl;
    cout << "+-----------------------------+";
    for (int j = to_string(pageFaults).length(); j < 8; j++) {
        cout << " ";
    }
    cout << "+" << endl;
}

int main() {
    vector<int> pageRequests = {1, 3, 0, 3, 5, 6, 3};
    int frameCount = 3;

    simulateOptimalPageReplacement(pageRequests, frameCount);

    return 0;
}

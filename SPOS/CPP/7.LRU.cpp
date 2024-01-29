#include <iostream>
#include <list>
#include <unordered_set>
#include <vector>

using namespace std;

void simulateLRUPageReplacement(const vector<int>& pageRequests, int frameCount) {
    list<int> pageFrames;
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
            if (pageFrames.size() == frameCount) {
                int removedPage = pageFrames.front();
                pageFrames.pop_front();
                pageSet.erase(removedPage);
            }
            pageFrames.push_back(page);
            pageSet.insert(page);
            pageFaults++;
            
            for (int frame : pageFrames) {
                cout << "       " << frame;
            }
            
            for (int j = pageFrames.size(); j < frameCount; j++) {
                cout << "                ";
            }

            cout << "| Page fault (F: " << pageFaults << ") |" << endl;
        } else {
            pageFrames.remove(page);
            pageFrames.push_back(page);
            pageHits++;
            
            for (int frame : pageFrames) {
                cout << "       " << frame;
            }
            
            for (int j = pageFrames.size(); j < frameCount; j++) {
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

    simulateLRUPageReplacement(pageRequests, frameCount);

    return 0;
}

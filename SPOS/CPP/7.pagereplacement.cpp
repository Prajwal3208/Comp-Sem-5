#include <iostream>
#include <list>
#include <unordered_set>
#include <vector>

using namespace std;

void simulateFIFOPageReplacement(const vector<int>& pageRequests, int frameCount) {
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
    vector<int> pageRequests = {4, 7, 6, 1, 7, 6, 1, 2, 7, 2};
    int frameCount = 3;

    cout << "FIFO Page Replacement Algorithm:" << endl;
    simulateFIFOPageReplacement(pageRequests, frameCount);
    
    cout << "LRU Page Replacement Algorithm:" << endl;
    simulateLRUPageReplacement(pageRequests, frameCount);
    
    cout << "Optimal Page Replacement Algorithm:" << endl;
    simulateOptimalPageReplacement(pageRequests, frameCount);

    return 0;
}

#include <iostream>
#include <vector>
#include <climits>

using namespace std;

struct Process {
    int id;
    int arrival_time;
    int burst_time;
    int priority;
};

void Priority_NonPreemptive(vector<Process>& processes) {
    cout << "Priority Scheduling (Non-Preemptive):" << endl;
    int n = processes.size();
    int time = 0;
    vector<bool> executed(n, false);

    while (true) {
        int highest_priority = INT_MAX;
        int highest_index = -1;

        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= time && !executed[i] && processes[i].priority < highest_priority) {
                highest_priority = processes[i].priority;
                highest_index = i;
            }
        }

        if (highest_index == -1) {
            time++;
        } else {
            executed[highest_index] = true;
            time += processes[highest_index].burst_time;
            cout << "Process " << processes[highest_index].id << " is executing." << endl;
            cout << "Process " << processes[highest_index].id << " completed at time " << time << endl;
        }

        if (time >= INT_MAX)
            break;
    }

    cout << "------------------------" << endl;
}

int main() {
    vector<Process> processes = {
        {1, 0, 5, 2},
        {2, 2, 3, 1},
        {3, 3, 2, 3},
        {4, 5, 8, 4}
    };

    Priority_NonPreemptive(processes);
    
    return 0;
}

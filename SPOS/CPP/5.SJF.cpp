#include <iostream>
#include <vector>
#include <climits>

using namespace std;

struct Process {
    int id;
    int arrival_time;
    int burst_time;
};

void SJF_Preemptive(vector<Process>& processes) {
    cout << "SJF Scheduling (Preemptive):" << endl;
    int n = processes.size();
    int time = 0;
    int completed = 0;
    
    vector<int> remaining_time(n);
    vector<bool> executed(n, false);

    for (int i = 0; i < n; i++) {
        remaining_time[i] = processes[i].burst_time;
    }

    while (completed < n) {
        int min_burst = INT_MAX;
        int min_index = -1;

        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= time && !executed[i] && remaining_time[i] < min_burst) {
                min_burst = remaining_time[i];
                min_index = i;
            }
        }

        if (min_index == -1) {
            time++;
        } else {
            remaining_time[min_index]--;
            time++;
            cout << "Process " << processes[min_index].id << " is executing." << endl;

            if (remaining_time[min_index] == 0) {
                completed++;
                executed[min_index] = true;
                cout << "Process " << processes[min_index].id << " completed at time " << time << endl;
            }
        }
    }

    cout << "------------------------" << endl;
}

int main() {
    vector<Process> processes = {
        {1, 0, 5},
        {2, 2, 3},
        {3, 3, 2},
        {4, 5, 8}
    };

    SJF_Preemptive(processes);
    
    return 0;
}

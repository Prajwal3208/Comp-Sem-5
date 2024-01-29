#include <iostream>
#include <vector>

using namespace std;

struct Process {
    int id;
    int arrival_time;
    int burst_time;
};

void FCFS(vector<Process>& processes) {
    cout << "FCFS Scheduling:" << endl;
    int time = 0;
    
    for (Process& p : processes) {
        time = max(time, p.arrival_time);
        cout << "Process " << p.id << " is executing." << endl;
        time += p.burst_time;
        cout << "Process " << p.id << " completed at time " << time << endl;
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

    FCFS(processes);
    
    return 0;
}

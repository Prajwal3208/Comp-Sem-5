#include <iostream>
#include <vector>
#include <climits>
#include <queue>

using namespace std;

struct Process {
    int id;
    int arrival_time;
    int burst_time;
    int priority;
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

void RoundRobin(vector<Process>& processes, int time_slice) {
    cout << "Round Robin Scheduling:" << endl;
    int n = processes.size();
    int time = 0;
    int completed = 0;

    queue<int> process_queue;
    vector<int> remaining_time(n);

    for (int i = 0; i < n; i++) {
        remaining_time[i] = processes[i].burst_time;
        process_queue.push(i);
    }

    while (completed < n) {
        int current_process = process_queue.front();
        process_queue.pop();

        if (remaining_time[current_process] > time_slice) {
            remaining_time[current_process] -= time_slice;
            time += time_slice;
            cout << "Process " << processes[current_process].id << " is executing." << endl;
            process_queue.push(current_process);
        } else {
            time += remaining_time[current_process];
            remaining_time[current_process] = 0;
            cout << "Process " << processes[current_process].id << " is executing." << endl;
            cout << "Process " << processes[current_process].id << " completed at time " << time << endl;
            completed++;
        }
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

    int choice;
    cout << "Choose a scheduling algorithm:" << endl;
    cout << "1. FCFS" << endl;
    cout << "2. SJF Preemptive" << endl;
    cout << "3. Priority Non-Preemptive" << endl;
    cout << "4. Round Robin" << endl;
    cin >> choice;

    switch (choice) {
        case 1:
            FCFS(processes);
            break;
        case 2:
            SJF_Preemptive(processes);
            break;
        case 3:
            Priority_NonPreemptive(processes);
            break;
        case 4:
            int time_slice;
            cout << "Enter time slice for Round Robin: ";
            cin >> time_slice;
            RoundRobin(processes, time_slice);
            break;
        default:
            cout << "Invalid choice." << endl;
            break;
    }

    return 0;
}

class Process:
    def __init__(self, process_id, burst_time, priority):
        self.process_id = process_id
        self.burst_time = burst_time
        self.priority = priority

def priority_scheduling(processes):
    processes.sort(key=lambda x: x.priority)
    waiting_time = [0]

    for i in range(1, len(processes)):
        waiting_time.append(waiting_time[i - 1] + processes[i - 1].burst_time)

    turnaround_time = [waiting_time[i] + processes[i].burst_time for i in range(len(processes))]

    avg_waiting_time = sum(waiting_time) / len(processes)
    avg_turnaround_time = sum(turnaround_time) / len(processes)

    print("\nGantt Chart:")
    for i in range(len(processes)):
        print(f"+{'-' * processes[i].burst_time}", end="+")
    print("+")

    for i in range(len(processes)):
        process_label = processes[i].process_id
        padding = (processes[i].burst_time - len(str(process_label))) // 2
        print(f"|{' ' * padding}{process_label}{' ' * padding}", end="|")
    print("\n", end="")

    current_time = 0
    for i in range(len(processes)):
        print(f"{current_time:^{processes[i].burst_time}}", end="")
        current_time += processes[i].burst_time

        if i == len(processes) - 1:
            print(f"{current_time:^{processes[i].burst_time}}", end="")
    print("\n")

    print("Process\tBurst Time\tPriority\tWaiting Time\tTurnaround Time")
    for i in range(len(processes)):
        print(f"{processes[i].process_id}\t\t\t{processes[i].burst_time}\t\t\t{processes[i].priority}\t\t\t{waiting_time[i]}\t\t\t{turnaround_time[i]}")

    print(f"\nAverage Waiting Time: {avg_waiting_time}")
    print(f"Average Turnaround Time: {avg_turnaround_time}")

if __name__ == "__main__":
    num_processes = int(input("Enter the number of processes: "))
    processes = []

    for i in range(num_processes):
        process_id = input(f"Enter the ID of Process {i + 1}: ")
        burst_time = int(input(f"Enter the burst time for Process {i + 1}: "))
        priority = int(input(f"Enter the priority for Process {i + 1}: "))
        processes.append(Process(process_id, burst_time, priority))

    priority_scheduling(processes)

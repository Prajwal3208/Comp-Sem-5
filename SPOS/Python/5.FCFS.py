def fcfs(processes, burst_time):
    n = len(processes)
    waiting_time = [0]

    for i in range(1, n):
        waiting_time.append(waiting_time[i - 1] + burst_time[i - 1])
        
    turnaround_time = [waiting_time[i] + burst_time[i] for i in range(n)]
    
    avg_waiting_time = sum(waiting_time) / n
    avg_turnaround_time = sum(turnaround_time) / n

    print("\nGantt Chart:")
    for i in range(n):
        print(f"+{'-' * burst_time[i]}", end="+")
    print("+")

    for i in range(n):
        process_label = processes[i]
        padding = (burst_time[i] - len(process_label)) // 2
        print(f"|{' ' * padding}{process_label}{' ' * padding}", end="|")
    print("\n", end="")

    current_time = 0
    for i in range(n):
        print(f"{current_time:^{burst_time[i]}}", end="")
        current_time += burst_time[i]

        if i == n - 1:
            print(f"{current_time:^{burst_time[i]}}", end="")
    print("\n")

    print("Process\tBurst Time\tWaiting Time\tTurnaround Time")
    for i in range(n):
        print(f"{processes[i]}\t\t\t{burst_time[i]}\t\t\t{waiting_time[i]}\t\t\t{turnaround_time[i]}")

    print(f"\nAverage Waiting Time: {avg_waiting_time}")
    print(f"Average Turnaround Time: {avg_turnaround_time}")

if __name__ == "__main__":

    num_processes = int(input("Enter the number of processes: "))
    processes = []
    burst_time = []

    for i in range(num_processes):
        process_name = input(f"Enter the name of Process {i + 1}: ")
        process_burst_time = int(input(f"Enter the burst time for Process {i + 1}: "))
        processes.append(process_name)
        burst_time.append(process_burst_time)

    fcfs(processes, burst_time)

class Process:
    def __init__(self, process_id, arrival_time, burst_time):
        self.process_id = process_id
        self.arrival_time = arrival_time
        self.burst_time = burst_time
        self.remaining_time = burst_time

def sjf_preemptive(processes):
    time_chart = []
    total_time = 0
    processes.sort(key=lambda x: (x.arrival_time, x.burst_time))

    while processes:
        ready_processes = [p for p in processes if p.arrival_time <= total_time]
        if not ready_processes:
            total_time += 1
            time_chart.append(None)
            continue

        shortest_job = min(ready_processes, key=lambda x: x.remaining_time)
        shortest_job.remaining_time -= 1
        total_time += 1
        time_chart.append(shortest_job.process_id)

        if shortest_job.remaining_time == 0:
            processes.remove(shortest_job)

    return time_chart

if __name__ == "__main__":
    # Example processes
    processes = [
        Process(1, 0, 5),
        Process(2, 1, 3),
        Process(3, 2, 8),
        Process(4, 3, 6),
    ]

    time_chart = sjf_preemptive(processes)

    # Display the time chart
    print("Time Chart:", time_chart)

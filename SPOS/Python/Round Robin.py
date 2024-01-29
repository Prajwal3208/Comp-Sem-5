class Process:
    def __init__(self, process_id, burst_time):
        self.process_id = process_id
        self.burst_time = burst_time
        self.remaining_time = burst_time

def round_robin(processes, time_quantum):
    time_chart = []
    total_time = 0

    while processes:
        for process in processes:
            if process.remaining_time > 0:
                if process.remaining_time <= time_quantum:
                    total_time += process.remaining_time
                    time_chart.append((process.process_id, total_time))
                    process.remaining_time = 0
                else:
                    total_time += time_quantum
                    time_chart.append((process.process_id, total_time))
                    process.remaining_time -= time_quantum

        # Remove completed processes
        processes = [p for p in processes if p.remaining_time > 0]

    return time_chart

if __name__ == "__main__":
    # Example processes
    processes = [
        Process(1, 10),
        Process(2, 5),
        Process(3, 8),
        Process(4, 2),
    ]

    time_quantum = 2

    time_chart = round_robin(processes, time_quantum)

    # Display the time chart
    print("Time Chart:", time_chart)

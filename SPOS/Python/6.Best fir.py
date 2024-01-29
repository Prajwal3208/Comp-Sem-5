class MemoryBlock:
    def __init__(self, size, allocated=False, process_id=None):
        self.size = size
        self.allocated = allocated
        self.process_id = process_id

def best_fit(memory_blocks, process_size, process_name):
    best_fit_block = None

    for block in memory_blocks:
        if not block.allocated and block.size >= process_size:
            if best_fit_block is None or block.size < best_fit_block.size:
                best_fit_block = block

    if best_fit_block is not None:
        best_fit_block.allocated = True
        best_fit_block.process_id = process_name
        return True
    else:
        return False

def display_memory_status(memory_blocks):
    print("Memory Block\tSize\tStatus\t\tProcess ID")
    for i, block in enumerate(memory_blocks, start=1):
        print(f"{i}\t\t\t{block.size}\t\t\t{'Allocated' if block.allocated else 'Free'}\t\t\t{block.process_id}")

if __name__ == "__main__":

    num_blocks = int(input("Enter the number of memory blocks: "))
    memory_blocks = [MemoryBlock(int(input(f"Enter size for block {i+1}: "))) for i in range(num_blocks)]

    num_processes = int(input("Enter the number of processes: "))
    processes = [(int(input(f"Enter size for process {i+1}: ")), input(f"Enter name for process {i+1}: ")) for i in range(num_processes)]

    for process_size, process_name in processes:
        success = best_fit(memory_blocks, process_size, process_name)
        if success:
            print(f"Allocated {process_size} units to process {process_name}.")
        else:
            print(f"Failed to allocate {process_size} units. No suitable block found for process {process_name}.")

    display_memory_status(memory_blocks)

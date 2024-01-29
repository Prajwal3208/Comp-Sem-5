class MemoryBlock:
    def __init__(self, size, allocated=False, process_id=None):
        self.size = size
        self.allocated = allocated
        self.process_id = process_id

def next_fit(memory_blocks, process_size, process_name, last_allocated_index):
    num_blocks = len(memory_blocks)

    for i in range(num_blocks):
        index = (last_allocated_index + i) % num_blocks
        block = memory_blocks[index]

        if not block.allocated and block.size >= process_size:
            block.allocated = True
            block.process_id = process_name
            return index

    return None

def display_memory_status(memory_blocks):
    print("Memory Block\tSize\tStatus\tProcess ID")
    for i, block in enumerate(memory_blocks, start=1):
        print(f"{i}\t\t\t{block.size}\t{'Allocated' if block.allocated else 'Free'}\t{block.process_id}")

if __name__ == "__main__":
    num_blocks = int(input("Enter the number of memory blocks: "))
    memory_blocks = [MemoryBlock(int(input(f"Enter size for block {i+1}: "))) for i in range(num_blocks)]

    num_processes = int(input("Enter the number of processes: "))
    processes = [(int(input(f"Enter size for process {i+1}: ")), input(f"Enter name for process {i+1}: ")) for i in range(num_processes)]

    last_allocated_index = 0

    for process_size, process_name in processes:
        index = next_fit(memory_blocks, process_size, process_name, last_allocated_index)
        if index is not None:
            print(f"Allocated {process_size} units to process {process_name}.")
            last_allocated_index = index
        else:
            print(f"Failed to allocate {process_size} units. No suitable block found for process {process_name}.")

    display_memory_status(memory_blocks)

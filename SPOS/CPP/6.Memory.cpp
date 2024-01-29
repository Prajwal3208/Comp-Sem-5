#include <iostream>
#include <vector>
#include <limits>

using namespace std;

struct MemoryBlock {
    int size;
    int process_id;
};


void allocateMemory(vector<MemoryBlock>& memory, int process_id, int process_size, const string& strategy) {
    int index = -1;

    if (strategy == "Best") {
        int min_size = numeric_limits<int>::max();
        for (int i = 0; i < memory.size(); i++) {
            if (memory[i].process_id == -1 && memory[i].size >= process_size && memory[i].size < min_size) {
                min_size = memory[i].size;
                index = i;
            }
        }
    } else if (strategy == "First") {
        for (int i = 0; i < memory.size(); i++) {
            if (memory[i].process_id == -1 && memory[i].size >= process_size) {
                index = i;
                break;
            }
        }
    } else if (strategy == "Next") {
        static int last_index = 0;
        for (int i = last_index; i < memory.size(); i++) {
            if (memory[i].process_id == -1 && memory[i].size >= process_size) {
                index = i;
                last_index = (i + 1) % memory.size();
                break;
            }
        }
        if (index == -1) {
            for (int i = 0; i < last_index; i++) {
                if (memory[i].process_id == -1 && memory[i].size >= process_size) {
                    index = i;
                    last_index = (i + 1) % memory.size();
                    break;
                }
            }
        }
    } else if (strategy == "Worst") {
        int max_size = -1;
        for (int i = 0; i < memory.size(); i++) {
            if (memory[i].process_id == -1 && memory[i].size >= process_size && memory[i].size > max_size) {
                max_size = memory[i].size;
                index = i;
            }
        }
    }

    if (index != -1) {
        memory[index].process_id = process_id;
        cout << "Process " << process_id << " of size " << process_size << " placed in block " << index << " using " << strategy << " Fit.\n";
    } else {
        cout << "Process " << process_id << " of size " << process_size << " cannot be placed using " << strategy << " Fit.\n";
    }
}

void displayMemory(const vector<MemoryBlock>& memory) {
    cout << "Memory Block Allocation:\n";
    for (int i = 0; i < memory.size(); i++) {
        cout << "Block " << i << ": Size = " << memory[i].size << ", Process ID = ";
        if (memory[i].process_id != -1) {
            cout << memory[i].process_id;
        } else {
            cout << "Empty";
        }
        cout << endl;
    }
}

int main() {
    int num_blocks;

    cout << "Enter the number of memory blocks: ";
    cin >> num_blocks;

    vector<MemoryBlock> memory(num_blocks);

    for (int i = 0; i < num_blocks; i++) {
        cout << "Enter the size of memory block " << i << ": ";
        cin >> memory[i].size;
        memory[i].process_id = -1;
    }
	
    string strategy = "Best";

    while (true) {
        cout << "\nMemory Placement Strategies:\n";
        cout << "1. Best Fit\n";
        cout << "2. First Fit\n";
        cout << "3. Next Fit\n";
        cout << "4. Worst Fit\n";
        cout << "5. Add Process\n";
        cout << "6. Show Memory Block Allocation\n";
        cout << "7. Exit\n";

        int choice;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 7) {
            break;
        }

        if (choice >= 1 && choice <= 4) {
            strategy = (choice == 1) ? "Best" : (choice == 2) ? "First" : (choice == 3) ? "Next" : "Worst";
            cout << "Selected strategy: " << strategy << " Fit\n";
        } else if (choice == 5) {
            int process_id, process_size;
            cout << "Enter process ID and size: ";
            cin >> process_id >> process_size;
            allocateMemory(memory, process_id, process_size, strategy);
        } else if (choice == 6) {
            displayMemory(memory);
        } else {
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}

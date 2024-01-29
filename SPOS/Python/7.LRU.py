class Page:
    def __init__(self, page_number):
        self.page_number = page_number
        self.referenced = 0

def lru(pages, page_frames):
    page_table = {}
    page_order = []

    page_faults = 0
    page_hits = 0

    for page_number in pages:
        if page_number in page_table:
            page_hits += 1
            page_table[page_number].referenced += 1
            # Move the accessed page to the end to represent it's the most recently used
            page_order.remove(page_table[page_number])
            page_order.append(page_table[page_number])
        else:
            page_faults += 1

            if len(page_table) == page_frames:
                # Remove the least recently used page (at the front of the list)
                removed_page = page_order.pop(0)
                del page_table[removed_page.page_number]

            new_page = Page(page_number)
            page_table[page_number] = new_page
            page_order.append(new_page)

        print(f"Cache after inserting page {page_number}: {[page.page_number for page in page_order]}")
        print(f"Hits: {page_hits}, Faults: {page_faults}\n")

    total_hits_and_faults = {"Hits": page_hits, "Faults": page_faults}
    return total_hits_and_faults

if __name__ == "__main__":
    pages_input = input("Enter the sequence of pages (space-separated): ")
    pages = [int(page) for page in pages_input.split()]

    page_frames = int(input("Enter the number of page frames: "))

    total_hits_and_faults = lru(pages, page_frames)

    print(f"Total Hits: {total_hits_and_faults['Hits']}, Total Faults: {total_hits_and_faults['Faults']}")
    print(f"Hit Ratio: {total_hits_and_faults['Hits'] / len(pages)}")

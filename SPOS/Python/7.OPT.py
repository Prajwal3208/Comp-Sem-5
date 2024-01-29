def optimal_page_replacement(pages, page_frames):
    page_faults = 0
    page_hits = 0
    page_table = {}  # Dictionary to store the pages in page frames

    for i, page in enumerate(pages):
        print(f"\nPage Reference: {page}")

        if page not in page_table:
            page_faults += 1

            if len(page_table) < page_frames:
                page_table[page] = i  # Store the index of the next reference for each page
                print("Page Fault: Inserting", page)
            else:
                # Find the page in page frames with the maximum index of the next reference
                page_to_replace = min(page_table, key=page_table.get)
                del page_table[page_to_replace]
                page_table[page] = i
                print(f"Page Fault: Replacing {page_to_replace} with {page}")

        else:
            page_hits += 1
            print("Page Hit!")

        # Display the current state of page frames
        print("Page Frames: ", list(page_table.keys()))

    # Display hit ratio at the end
    total_references = len(pages)
    hit_ratio = page_hits / total_references
    print(f"\nHit Ratio: {page_hits}/{total_references} = {hit_ratio:.2%}")

    return page_faults

if __name__ == "__main__":
    # User input for pages
    pages_str = input("Enter the sequence of pages (e.g., 7 0 1 2): ")
    pages = [int(page) for page in pages_str.split()]

    # User input for page frames
    page_frames = int(input("Enter the number of page frames: "))

    total_page_faults = optimal_page_replacement(pages, page_frames)

    print(f"\nTotal Page Faults using Optimal: {total_page_faults}")

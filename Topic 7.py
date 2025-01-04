def heapify(arr, n, i):
    largest = i
    left = 2 * i + 1
    right = 2 * i + 2

    if left < n and arr[left] > arr[largest]:
        largest = left

    if right < n and arr[right] > arr[largest]:
        largest = right

    if largest != i:
        arr[i], arr[largest] = arr[largest], arr[i]
        heapify(arr, n, largest)

def heap_sort(arr):
    n = len(arr)

    # Build a max heap
    for i in range(n // 2 - 1, -1, -1):
        heapify(arr, n, i)

    # Extract elements from the heap
    for i in range(n - 1, 0, -1):
        arr[i], arr[0] = arr[0], arr[i]  # Swap
        heapify(arr, i, 0)

# Example Usage
data = [("Banana", 2), ("Apple", 5), ("Carrot", 1), ("Milk", 3)]
# Sorting based on priority (e.g., price)
priorities = [item[1] for item in data]

heap_sort(priorities)

# Map sorted priorities back to items
sorted_data = sorted(data, key=lambda x: x[1])

# Display sorted data
print("Sorted Data (by priority):")
for item in sorted_data:
    print(f"{item[0]} - Priority {item[1]}")

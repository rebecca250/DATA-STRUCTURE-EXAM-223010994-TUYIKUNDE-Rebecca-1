class Stack:
    def __init__(self):
        self.stack = []

    def push(self, item):
        self.stack.append(item)
        print(f"Item '{item}' added to the stack.")

    def pop(self):
        if not self.stack:
            print("Stack is empty. No items to remove.")
            return None
        removed_item = self.stack.pop()
        print(f"Item '{removed_item}' removed from the stack.")
        return removed_item

    def peek(self):
        if not self.stack:
            print("Stack is empty.")
            return None
        print(f"Top item: {self.stack[-1]}")
        return self.stack[-1]

    def display(self):
        if not self.stack:
            print("Stack is empty.")
        else:
            print("Current Stack (top to bottom):", " -> ".join(self.stack[::-1]))

# Example Usage
stack = Stack()

# Add scanned items
stack.push("Item A")
stack.push("Item B")
stack.push("Item C")

# Display stack
stack.display()

# Remove last scanned item
stack.pop()

# View the current top item
stack.peek()

# Display updated stack
stack.display()

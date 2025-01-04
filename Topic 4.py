class CircularQueue:
    def __init__(self, size):
        self.queue = [None] * size
        self.max_size = size
        self.front = self.rear = -1

    def enqueue(self, order):
        if (self.rear + 1) % self.max_size == self.front:
            print("Queue full. Cannot add:", order)
            return False
        self.rear = (self.rear + 1) % self.max_size
        if self.front == -1: self.front = 0
        self.queue[self.rear] = order
        return True

    def dequeue(self):
        if self.front == -1:
            print("Queue empty. Nothing to remove.")
            return None
        removed = self.queue[self.front]
        self.queue[self.front] = None
        if self.front == self.rear:
            self.front = self.rear = -1  # Reset queue
        else:
            self.front = (self.front + 1) % self.max_size
        return removed

    def display(self):
        if self.front == -1:
            print("Queue is empty.")
            return
        i = self.front
        while True:
            print(self.queue[i], end=" ")
            if i == self.rear: break
            i = (i + 1) % self.max_size
        print()

# Example Usage
q = CircularQueue(3)
q.enqueue("Order 1")
q.enqueue("Order 2")
q.enqueue("Order 3")
q.enqueue("Order 4")  
q.display()           
q.dequeue()
q.enqueue("Order 4")  
q.display()           

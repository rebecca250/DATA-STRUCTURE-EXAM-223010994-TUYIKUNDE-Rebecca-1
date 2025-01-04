# Circular Queue Class
class CircularQueue:
    def __init__(self, size):
        self.size = size
        self.queue = [None] * size
        self.front = self.rear = -1

    def enqueue(self, item):
        if (self.rear + 1) % self.size == self.front:
            print("Queue is full.")
        elif self.front == -1:
            self.front = self.rear = 0
            self.queue[self.rear] = item
        else:
            self.rear = (self.rear + 1) % self.size
            self.queue[self.rear] = item

    def dequeue(self):
        if self.front == -1:
            print("Queue is empty.")
            return None
        elif self.front == self.rear:
            item = self.queue[self.front]
            self.front = self.rear = -1
            return item
        else:
            item = self.queue[self.front]
            self.front = (self.front + 1) % self.size
            return item

    def display(self):
        if self.front == -1:
            print("Queue is empty.")
        else:
            i = self.front
            while i != self.rear:
                print(self.queue[i], end=" ")
                i = (i + 1) % self.size
            print(self.queue[self.rear])

# Example Usage - CircularQueue
cq = CircularQueue(3)
cq.enqueue("Customer 1")
cq.enqueue("Customer 2")
cq.enqueue("Customer 3")
cq.display()
print("Processing:", cq.dequeue())
cq.display()

# Order Queue Class
class OrderQueue:
    def __init__(self, size):
        self.size = size
        self.queue = [None] * size
        self.front = self.rear = -1

    def add_order(self, order):
        if (self.rear + 1) % self.size == self.front:
            print("Order queue is full. Removing the oldest order.")
            self.dequeue()
        elif self.front == -1:
            self.front = self.rear = 0
            self.queue[self.rear] = order
        else:
            self.rear = (self.rear + 1) % self.size
            self.queue[self.rear] = order

    def dequeue(self):
        if self.front == -1:
            print("No orders to process.")
            return None
        elif self.front == self.rear:
            order = self.queue[self.front]
            self.front = self.rear = -1
            return order
        else:
            order = self.queue[self.front]
            self.front = (self.front + 1) % self.size
            return order

    def display_orders(self):
        if self.front == -1:
            print("No orders to display.")
        else:
            i = self.front
            while i != self.rear:
                print(self.queue[i], end=" ")
                i = (i + 1) % self.size
            print(self.queue[self.rear])

# Example Usage - OrderQueue
order_queue = OrderQueue(3)
order_queue.add_order("Order 1")
order_queue.add_order("Order 2")
order_queue.add_order("Order 3")
order_queue.add_order("Order 4")
order_queue.display_orders()
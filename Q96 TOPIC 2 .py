# Binary Tree Node Class
class TreeNode:
    def __init__(self, product, price):
        self.product = product
        self.price = price
        self.left = None
        self.right = None

# Stack Class
class Stack:
    def __init__(self):
        self.items = []

    def push(self, item):
        self.items.append(item)

    def pop(self):
        if not self.is_empty():
            return self.items.pop()

    def is_empty(self):
        return len(self.items) == 0

# Binary Tree Class
class BinaryTree:
    def __init__(self):
        self.root = None

    def insert(self, product, price):
        if not self.root:
            self.root = TreeNode(product, price)
        else:
            self._insert_recursive(self.root, product, price)

    def _insert_recursive(self, node, product, price):
        if product < node.product:
            if node.left:
                self._insert_recursive(node.left, product, price)
            else:
                node.left = TreeNode(product, price)
        else:
            if node.right:
                self._insert_recursive(node.right, product, price)
            else:
                node.right = TreeNode(product, price)

    def inorder_traversal(self, node):
        if node:
            self.inorder_traversal(node.left)
            print(f"{node.product}: ${node.price}")
            self.inorder_traversal(node.right)

# Example Usage - BinaryTree and Stack
binary_tree = BinaryTree()
binary_tree.insert("Milk", 2.50)
binary_tree.insert("Bread", 1.20)
binary_tree.insert("Eggs", 3.00)

print("Products in the tree (inorder traversal):")
binary_tree.inorder_traversal(binary_tree.root)

stack = Stack()
stack.push("Scanned Milk")
stack.push("Scanned Bread")
print("Last scanned item:", stack.pop())
class TreeNode:
    def __init__(self, name):
        self.name = name
        self.children = []

    def add_child(self, child):
        self.children.append(child)

    def display(self, level=0):
        print(" " * level * 4 + self.name)
        for child in self.children:
            child.display(level + 1)

# Example Usage
root = TreeNode("Supermarket")

# Adding categories
fruits = TreeNode("Fruits")
vegetables = TreeNode("Vegetables")
dairy = TreeNode("Dairy")

root.add_child(fruits)
root.add_child(vegetables)
root.add_child(dairy)

# Adding items to categories
fruits.add_child(TreeNode("Apple"))
vegetables.add_child(TreeNode("Carrot"))
dairy.add_child(TreeNode("Milk"))

# Display the tree
root.display()

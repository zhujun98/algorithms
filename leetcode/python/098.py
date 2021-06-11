"""
98. Validate Binary Search Tree
"""


def validate(self, node, low, high) -> bool:
    if node is None:
        return True

    if low is not None and low.val >= node.val:
        return False
    if high is not None and high.val <= node.val:
        return False

    return self.validate(node.left, low, node) \
           and self.validate(node.right, node, high)


def isValidBST(self, root) -> bool:
    return self.validate(root, None, None)

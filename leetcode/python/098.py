"""
98. Validate Binary Search Tree
"""


def validate(node, low, high) -> bool:
    if node is None:
        return True

    if low is not None and low.val >= node.val:
        return False
    if high is not None and high.val <= node.val:
        return False

    return validate(node.left, low, node) and validate(node.right, node, high)


def isValidBST(root) -> bool:
    return validate(root, None, None)


class ValidateBSTInorder:
    def __init__(self):
        self._prev = None

    def validate(self, node):
        if node is None:
            return True

        if not self.validate(node.left):
            return False

        if self._prev is not None and self._prev.val >= node.val:
            return False

        self._prev = node
        return self.validate(node.right)

    def isValidBSTInorder(self, root) -> bool:
        return self.validate(root)

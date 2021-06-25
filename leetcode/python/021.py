"""
21. Merge Two Sorted Lists
"""


class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next


def mergeTwoLists(l1: ListNode, l2: ListNode) -> ListNode:
    if l1 is None:
        return l2
    if l2 is None:
        return l1

    prev_head = ListNode(-1)
    prev = prev_head
    while l1 is not None and l2 is not None:
        if l1.val < l2.val:
            prev.next = l1
            l1 = l1.next
        else:
            prev.next = l2
            l2 = l2.next
        prev = prev.next

    prev.next = l1 if l1 is not None else l2

    return prev_head.next

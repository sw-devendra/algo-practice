from __future__ import annotations
import typing

class Node:
    def __init__(self, val=0, next:Node = None, prev:Node = None) -> None:
        self.val = val
        self.next = next
        self.prev = prev

class Deque:
    def __init__(self) -> None:
        self.head=Node()
        self.tail = Node()
        self.head.next = self.tail
        self.tail.prev = self.head

    def addFront(self, val) -> Node:
        n = Node(val, self.head.next, self.head)
        self.head.next.prev = n
        self.head.next = n
        return n

    def remove(self, node: Node) -> None:
        # if not remove already
        if node.next != None:
            node.prev.next = node.next
            node.next.prev = node.prev
            node.prev, node.next = None, None

    def print(self):
        print("Deque")
        temp = self.head.next
        while temp!= self.tail:
            print(temp.val)
            temp = temp.next

if __name__ == '__main__':
    d = Deque()
    hashTable = dict()
    for i in range(1,11):
        hashTable[i] = d.addFront(i)

    d.print()

    print("Removing middle")
    n = hashTable[5]
    del hashTable[5]
    d.remove(n)
    d.print()

    print("Removing last")
    n = hashTable[1]
    del hashTable[1]
    d.remove(n)
    d.print()

    print("Removing first")
    n = hashTable[10]
    del hashTable[10]
    d.remove(n)
    d.print()


    

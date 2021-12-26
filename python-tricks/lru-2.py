# Well Tested (passed on leetcode)

from __future__ import annotations
import typing

class Node:
    def __init__(self, key =None, next: Node = None, prev: Node = None) -> None:
        pass

class DLQ:
    def __init__(self) -> None:
        self.head = Node()
        self.tail = Node()
        self.head.next = self.tail
        self.tail.prev = self.head

    def remove(self, node: Node) -> Node:
        lastNode = node.prev
        nextNode = node.next
        lastNode.next = nextNode
        nextNode.prev = lastNode
        node.next = node.last = None

        return node

    def removeLast(self) -> Node:
        if self.tail.prev != self.head:
            last = self.remove(self.tail.prev)
            return last

        return None

    def addFront(self, node: Node) -> Node:
        node.next = self.head.next
        node.prev = self.head
        self.head.next.prev = node
        self.head.next = node
        return node

    def addNew(self, key) -> Node:
        newNode = Node(key)
        return self.addFront(newNode)


class LRU:
    def __init__(self, size: int) -> None:
        self.size = size
        self.currentSize = 0
        self.dlq = DLQ()
        self.hash = dict()

    def evictCache(self) -> None:
        while self.currentSize >= self.size:
            lastNode = self.dlq.removeLast()
            del self.hash[lastNode.key]
            self.currentSize -= 1

    def put(self, key, val) -> None:
        if key in self.hash:
            node, __ = self.hash[key]
            self.dlq.remove(node)
            self.dlq.addFront(node)
            self.hash[key] = (node, val)

        else:
            if self.currentSize == self.size:
                self.evictCache()

            node = self.dlq.addNew(key)
            self.hash[key] = (node, val)

            self.currentSize += 1
            
    def get(self, key):
        if not key in self.hash:
            return None

        node, val = self.hash[key]
        self.dlq.remove(node)
        self.dlq.addFront(node)

        return val


if __name__ == "__main__":
    lru = LRU(2)

    lru.put("monday", 35)
    lru.put("sunday", 30)
    print(lru.get("monday"))
    print(lru.get("sunday"))
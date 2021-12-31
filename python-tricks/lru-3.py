class Node:
    def __init__(self, key=None, val = None, nxt = None, prv = None):
        self.key, self.val, self.nxt, self.prv = key, val, nxt, prv
        
class DLQ:
    def __init__(self):
        self.head, self.tail = Node(), Node()
        self.head.nxt = self.tail
        self.tail.prv = self.head
        
    def addFrontNode(self, node):
        # WARNING : sequence is VERY important here
        # In cross referencing objects, the sequence matters even in case of simultaneous assignments
        node.nxt, node.prv, self.head.nxt.prv, self.head.nxt = self.head.nxt, self.head, node, node
        return node
    
    def addFront(self, key, val):
        node = Node(key, val)
        self.addFrontNode(node)
        return node
    
    def remove(self, node):
        node.prv.nxt, node.nxt.prv, node.nxt, node.prv = node.nxt, node.prv, None, None
        return node
    
    def removeLast(self):
        node = self.tail.prv
        self.remove(node)
        return node

    
class LRU:
    def __init__(self, capacity):
        self.dlq = DLQ()
        self.hash = dict()
        self.capacity = capacity
        self.size = 0
        
    def put(self, key, val):
        if key in self.hash:
            node = self.hash[key]
            node.val = val
            self.dlq.remove(node)
            self.dlq.addFrontNode(node)
            return
        
        if self.size == self.capacity:
            node = self.dlq.removeLast()
            del self.hash[node.key]
            self.size -= 1
            
        node = self.dlq.addFront(key, val)
        self.hash[key] = node
        self.size += 1
        
    def get(self, key):
        if not key in self.hash:
            return -1
        
        node = self.hash[key]
        self.dlq.remove(node)
        self.dlq.addFrontNode(node)
        
        return node.val

if __name__ == "__main__":
    lru = LRU(2)
    lru.put("one", 1)
    lru.put("two", 2)
    lru.put("three",3)
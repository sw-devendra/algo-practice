trie = {}

def create(arr):
    for a in arr:
        node = trie
        for ch in a:
            node = node.setdefault(ch,{})
        node.setdefault('$',{})

def find(s: str, node):
    if len(s) == 0:
        return '$' in node
    if not s[0] in node:
        return False
    return find(s[1:], node[s[0]])

create(arr = ["devendra","agarwal","dev","again"])

tc = [("devendra",True),("aga", False),("agarwal",True),("dev",True), ("d", False)]

for s, res in tc:
    print(s, "expected:", res, "actual:", find(s, trie))
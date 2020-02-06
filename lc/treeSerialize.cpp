#include <iostream>
using namespace std;  
  
  // Definition for a binary tree node.
  struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode(int x) : val(x), left(NULL), right(NULL) {}
  };
 
class Codec {
public:
    struct Entry{
        int val;
        int left;
        int right;
    };
    int countLen(TreeNode *n) {
        if (!n)
            return 0;
        
        return countLen(n->left) + countLen(n->right) + 1;
    }
    int serialize(Entry *v, int nextId, TreeNode *n) {
        if(!n) {
            return -1;
        }
        int leftId = serialize(v, nextId, n->left);
        if (leftId != -1) {
            nextId = leftId + 1;
        }
        int rightId = serialize(v, nextId, n->right);
        Entry e = {n->val, leftId, rightId};
        if (rightId != -1) {
            nextId = rightId + 1;
        }
        v[nextId] = e;
        return nextId;
        
    }
    
    
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        int l = countLen(root);
        if (l) {
            Entry* v = new Entry[l];
            serialize(v, 0, root);
            string res = string((char*)&l,sizeof(int)) + string((char*)v, sizeof(Entry)*l);
            delete []v;
            return res;           
        }
        return string((char*)&l,sizeof(int)); // Empty tree case, when l == 0

    }

    TreeNode *deserialize(Entry *v, int id) {
        if (id == -1) 
            return 0;
        TreeNode *n = new TreeNode(v[id].val);
        n->left = deserialize(v, v[id].left);
        n->right = deserialize(v, v[id].right);
        return n;
    }
    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        int l = *((int*)data.data());
        Entry *v = (Entry*)((char*)data.data() + sizeof(int));
        return deserialize(v, l-1);
    }
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));
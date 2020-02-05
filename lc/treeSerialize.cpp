/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Codec {
public:
    struct Entry{
        int val;
        int left;
        int right;
    }
    int countLen(TreeNode *n) {
        if (!n)
            return 0;
        
        countLen(n->left) + countLen(n->right) + 1;
    }
    int serialize(vector<Entry> &v, int nextId, TreeNode *n) {
        if(!n) {
            return -1;
        }
        int leftId = serialize(v, nextId, n->left);
        if (leftId != -1)) {
            nextId = leftId + 1;
        }
        int rightId = serialize(v, nextId, n->right);
        Entry e = {n->val, leftId, rightId};
        if (rightId != -1)) {
            nextId = rightId + 1;
        }
        v[nextId] = e;
        return nextId;
        
    }
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        if (root == NULL)
            return string();
        int l = countLen(n);
        vector<Entry> v(l);
        serialize(v, 0, root);
        for ()
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        
    }
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));
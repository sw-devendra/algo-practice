// https://leetcode.com/problems/concatenated-words/
// All TCs pass

#include <vector>
#include <string>

#define ALPH_SIZE 26

using namespace std;
#define ALPH_SIZE 26

class Solution {
private:
    struct TrieNode {
        TrieNode* children[ALPH_SIZE];
        bool isEnd;
        TrieNode() :isEnd(false) {
            for (int i = 0; i < ALPH_SIZE; i++) {
                children[i] = 0;
            }
        }
        ~TrieNode() {
            for (auto ch : children) {
                if (ch)
                    delete ch;
            }
        }
    };
    TrieNode* root;
    vector<int> breakPoints;

    int chKey(char ch) {
        return ch - 'a';
    }
    void insert(TrieNode* node, string& w, int id) {
        if (id == w.length()) {
            node->isEnd = true;
            return;
        }
        int key = chKey(w[id]);
        if (node->children[key] == 0) {
            node->children[key] = new TrieNode();
        }
        insert(node->children[key], w, id + 1);
    }

    bool isConcat(TrieNode* n, string& w, int id) {
        if (id == w.length()) {
            return n->isEnd;
        }
        if (n->isEnd) {
            breakPoints.push_back(id);
            bool remainingConcat = isConcat(root, w, id);
            if (remainingConcat) {
                return true;
            }
            breakPoints.pop_back();
        }
        int key = chKey(w[id]);
        if (n->children[key] == 0) {
            return false;
        }
        return isConcat(n->children[key], w, id + 1);
    }


public:
    vector<string> findAllConcatenatedWordsInADict(vector<string>& words) {
        root = new TrieNode;
        for (auto w : words) {
            if (w.length() == 0) {
                continue;
            }
            insert(root, w, 0);
        }
        vector<string> results;
        for (auto w : words) {
            breakPoints = vector<int>();
            if (isConcat(root, w, 0) && breakPoints.size() != 0) {
                results.push_back(w);
            }
        }
        return results;

        delete root;
    }
};

int main() {
    vector<string> words = { "cat", "cats", "catsdogcats", "dog", "dogcatsdog", "hippopotamuses", "rat", "ratcatdogcat" };
    Solution s;
    auto concats = s.findAllConcatenatedWordsInADict(words);
    return 0;
}

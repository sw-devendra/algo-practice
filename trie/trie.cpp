#include <iostream>

using namespace std;

#define ALPH_SIZE 26

struct TrieNode {
    static int nodeCnt;
    TrieNode *child[ALPH_SIZE];
    bool leaf;
    int count;
    TrieNode() {
        for (int i=0; i<ALPH_SIZE; i++)
            child[i] = 0;
        leaf  = false;
        count = 0;
        nodeCnt++;
    }
    ~TrieNode() {
        nodeCnt--;
        for (int i=0; i<ALPH_SIZE; i++)
                    delete child[i];       
    }
};
int TrieNode::nodeCnt;

int charToId(char ch) {
    return ch - 'a';
}

TrieNode *insert(char *s, TrieNode *tn) {
    if (!tn) {
        tn = new TrieNode;
    }
    tn->count++;
    if (*s == 0) {
        tn->leaf = true;
    }
    else {
        int id = charToId(*s);
        tn->child[id] = insert(s+1, tn->child[id]);
    }

    return tn;
}

TrieNode *find(char *s, TrieNode *tn) {
    if (!tn)
        return 0;
    
    if (*s == 0) {
        return tn;
    }
    return find(s+1, tn->child[charToId(*s)]);
}


////////////// TESTING
TrieNode *root;
char simpleTC[10][11] = {
    "aa",
    "a",
    "ab",
    "zzz",
    "dev",
    "devendra",
    "agarwal",
    "agar",
    "zzzzzzzzzz",
    "abc"
};

void insertAll(char (*s)[11], int count) {
    for(int i=0; i<count; i++) {
        root = insert(s[i], root);
    }
}

void findAll(char (*s)[11], int count) {
        for(int i=0; i<count; i++) {
                TrieNode *tn = find(s[i], root);
                if (tn) {
                    cout<<s[i]<<" : Count " << tn->count<< " : leaf "<<tn->leaf<<endl;
                }
        }
        char temp[11] = "notexists";
        TrieNode *tn = find(temp, root);
        if (!tn) {
            cout<<"xxxx Not found" <<endl;
        }

}

int main() {

    insertAll(simpleTC, 10);
    cout<<" nodeCnt: "<<TrieNode::nodeCnt <<endl;
    findAll(simpleTC, 10);
    delete root;
    cout<<" nodeCnt: "<<TrieNode::nodeCnt<<endl;
    return 0;
}
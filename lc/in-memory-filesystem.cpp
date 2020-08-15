// Passing all TCs
// https://leetcode.com/problems/design-in-memory-file-system/
//  Failing TC  ["FileSystem","mkdir","ls","ls","mkdir","ls","ls","addContentToFile","ls","ls","ls"]
// [[],["/goowmfn"],["/goowmfn"],["/"],["/z"],["/"],["/"],["/goowmfn/c","shetopcy"],["/z"],["/goowmfn/c"],["/goowmfn"]]
#include <vector>
#include <memory>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

class FileSystem {
private:
    struct Node {
        vector<Node*> children;
        bool isFile;
        string name;
        string fileContent;
        Node(string n, bool isf = false) :isFile(isf), name(n) {
        }
        ~Node() {
            for (auto ch : children) {
                delete ch;
            }
        }
    };
    unique_ptr<Node> root;
private:
    vector<string> split(string path, char delit) {
        std::stringstream ss(path);
        std::string token;
        vector<string> pathParts;
        while (std::getline(ss, token, delit)) {
            pathParts.push_back(token);
        }
        return pathParts;
    }

    vector<string> listNode(Node* node) {
        vector<string> names;
        if (node->isFile) {
            names.push_back(node->name);
            return names;
        }

        for (auto ch : node->children) {
            names.push_back(ch->name);
        }
        sort(names.begin(), names.end());
        return names;
    }

    Node* getFinalNode(string path) {
        if (path == "/") {
            return root.get();
        }
        Node* currentNode = root.get();
        vector<string> parts = split(path, '/');
        for (int i = 1; i < parts.size(); i++) {
            auto name = parts[i];
            for (auto child : currentNode->children) {
                if (child->name == name) {
                    currentNode = child;
                    break;
                }
            }
        }

        return currentNode;
    }
public:
    FileSystem() :root(new Node("/")) {
    }

    vector<string> ls(string path) {
        return listNode(getFinalNode(path));
    }

    void mkdir(string path) {
        std::stringstream ss(path);
        std::string token;
        vector<string> pathParts;
        while (std::getline(ss, token, '/')) {
            pathParts.push_back(token);
        }
        Node* currentNode = root.get();
        for (int i = 1; i < pathParts.size(); i++) {
            Node* targetChild = 0;
            for (auto ch : currentNode->children) {
                if (ch->name == pathParts[i]) {
                    targetChild = ch;
                    currentNode = targetChild;
                    break;
                }
            }
            if (targetChild == 0) {
                targetChild = new Node(pathParts[i]);
                currentNode->children.push_back(targetChild);
            }
            currentNode = targetChild;
        }
    }

    void addContentToFile(string filePath, string content) {
        int id = filePath.rfind('/');
        Node* parentNode = 0;
        string baseName = filePath.substr(id + 1);
        if (id == 0) {
            parentNode = root.get();
        }
        else {
            parentNode = getFinalNode(filePath.substr(0, id));
        }
        Node* target = 0;
        for (auto child : parentNode->children) {
            if (child->name == baseName) {
                target = child;
                break;
            }
        }
        if (target == 0) {
            target = new Node(baseName, true);
            parentNode->children.push_back(target);
        }
        target->fileContent += content;
    }

    string readContentFromFile(string filePath) {
        Node* target = getFinalNode(filePath);
        return target->fileContent;
    }
};

/**
 * Your FileSystem object will be instantiated and called as such:
 * FileSystem* obj = new FileSystem();
 * vector<string> param_1 = obj->ls(path);
 * obj->mkdir(path);
 * obj->addContentToFile(filePath,content);
 * string param_4 = obj->readContentFromFile(filePath);
 */

//["FileSystem", "mkdir", "ls", "ls", "mkdir", "ls", "ls", "addContentToFile", "ls", "ls", "ls"]
// [[], ["/goowmfn"], ["/goowmfn"], ["/"], ["/z"], ["/"], ["/"], ["/goowmfn/c", "shetopcy"], ["/z"], ["/goowmfn/c"], ["/goowmfn"]]

int main() {
    FileSystem fs;
    fs.mkdir("/goowmfn");
    vector<string> files = fs.ls("/goowmfn");
    files = fs.ls("/");
    fs.mkdir("/z");
    files = fs.ls("/");
    files = fs.ls("/");
    fs.addContentToFile("/goowmfn/c", "shetopcy");
    files = fs.ls("/z");
    files = fs.ls("/goowmfn/c");
    files = fs.ls("/goowmfn");

    return 0;
}

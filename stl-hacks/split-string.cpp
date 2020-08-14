#include <iostream>
#include <sstream>
#include <vector>

using namespace std; 

vector<string> split(string path, char delit) {
    std::stringstream ss(path);
    std::string token;
    vector<string> pathParts;
    while (std::getline(ss, token, delit)) {
        pathParts.push_back(token);
    }
    return pathParts;
}
int main() {
    string path = "/dev/blue";

    auto pathParts = split(path, '/');
    for (auto p: pathParts)
        cout << p << endl;
    return 0;
}

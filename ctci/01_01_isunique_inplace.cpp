#include <iostream>
#include <algorithm>

using namespace std;
bool isunique(char *str, int len) {
    bool temp[256];

    sort(str, str + len);
    for (int i=0; i<=(len-2); i++) {
        if (str[i] == str[i+1]) {
            return false;
        }
    }
    return true;
}

int main() {
    char one[] = "devendra";
    char two[] = "dev";
    cout << isunique(one, 8) <<endl;
    cout << isunique(two, 3) << endl;
    return 0;
}
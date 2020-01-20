#include <iostream>

using namespace std;

bool isPermutation(string s1, string s2) {

    int cnt[256] = {0, };
    for (int i=0; i< s1.length(); i++) {
        cnt[s1[i]]++;
    }
    for (int i=0; i< s2.length(); i++) {
        cnt[s2[i]]--;
    }

    for (int i=0; i<256; i++) {
        if (cnt[i] != 0) {
            return false;
        }
    }

    return true;
}

int main() {

    cout<< isPermutation("dev", "ved") << endl;
    cout<< isPermutation("devendra", "ddd") << endl;
    return 0;
}


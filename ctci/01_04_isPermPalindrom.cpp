#include <iostream>

using namespace std;

bool isPermPalindrome(string str) {
    char alph[256] = {0,};
    for (int i=0; i<str.length(); i++) {
        alph[str[i]]++;
    }

    int oddCnt = 0;
    for (int i=0; i<256; i++) {
        if (alph[i]%2) {
            oddCnt++;
            if (oddCnt > 1) {
                return false;
            }
        }
    }

    return true;
}

int main() {
    cout<< isPermPalindrome("devdev") << endl;
    cout<< isPermPalindrome("Adevdev") << endl;
    cout<< isPermPalindrome("ABdevdev") << endl;
    cout<< isPermPalindrome("AAdevdev") << endl;

    return 0;
}
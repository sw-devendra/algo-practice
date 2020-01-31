#include <iostream>

using namespace std;

int cntDigits(int n) {
    if (!n) {
        return 1;
    }
    int cnt = 0;
    while(n) {
        cnt += 1;
        n /= 10;
    }

    return cnt;
}

int getPostCompLen(string s) {
    if (s.length() == 0)
        return 0;
    
    int lastCharCnt = 1;
    int postCompLen = 1;
    char lastChar = s[0];

    for (int i=1; i<= s.length(); i++) {
        if (s[i] == s[i-1]) {
            lastCharCnt += 1;
        }
        else {
            postCompLen += cntDigits(lastCharCnt);
            if (s[i]) {
                lastChar = s[i];
                lastCharCnt = 1;
                postCompLen += 1;
            }
            else {
                break;
            }
        }
    }

    return postCompLen;
}

void getDigits(char *dStr, int n) {
    int digitCnt = cntDigits(n);
    if (n == 0) {
        dStr[0] = '0';
    }
    dStr[digitCnt] = 0;
    while(n) {
        dStr[digitCnt-1] = n%10 + '0';
        digitCnt -= 1;
        n /= 10;
    }
}
string compressedStr(string s) {
    int postLen = getPostCompLen(s);

    if (postLen >= s.length()) {
        return s;
    }

    string compStr;
    compStr.reserve(postLen+1); // To check the changed capacity : cout << compStr.capacity() <<endl;
    compStr += s[0];
    
    int srcI = 1;
    int lastCharCnt = 1;
    for(;srcI <= s.length(); srcI++) {
        if (s[srcI] == s[srcI -1]) {
            lastCharCnt += 1;
        }
        else {
            char digits[11];
            getDigits(digits, lastCharCnt);
            compStr += digits;
            if (s[srcI])
                compStr += s[srcI];
            lastCharCnt = 1;
        }
    }

    return compStr;
}

int main() {
    string tcs[] = {
                    "dev",
                    "ddddeeeeevvvvv",
                    "a",
                    "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab"
    };

    for (auto s: tcs) {
        string cs = compressedStr(s);
        cout<<s<<" => "<< s.length() << " => " << cs << " => "<< cs.length() << endl;
    }
    
    return 0;
}
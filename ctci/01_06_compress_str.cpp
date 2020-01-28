#include <iostream>

using namespace std;

int countDigits(int n) {
    int cnt = 0;
    if (!n) { // 0 will also take one digit
        return 1;
    }
    while (n) {
        cnt++;
        n /= 10;
    }

    return cnt;
}

int copyNum(char *dest, int n) {
    int digitCnt = countDigits(n);
    int i = 0;
    while(n) {
        dest[digitCnt - i -1] = (n%10) + '0';
        i++;
        n = n/10;
    }
    return digitCnt;
}

char *compress(const char *str) {
    char *newStr = 0;
    if (!str) {
        return 0;
    }


    if (!str[0]) {
        newStr = new char[1];
        newStr[0] = 0;
        return newStr;
    }

    int len = 1;
    int lastCharCnt = 1;
    int compressedLen = 0;
    for (int i=1 ; str[i]; i++, len++) {
        if (str[i] == str[i-1]) {
            lastCharCnt++;
        }
        else {
            compressedLen = compressedLen + 1 + countDigits(lastCharCnt);
            lastCharCnt = 1;
        }
    }
    compressedLen = compressedLen + 1 + countDigits(lastCharCnt);

    if (compressedLen >= len) {
        newStr = new char[len + 1];
        int i = 0;
        while(newStr[i] = str[i])
         i++;
    }
    else {
        int lastCharCnt = 0;
        int j = 0, i=0;
        newStr = new char[compressedLen + 1];
        for(i=0, j=0; str[i]; i++) {
            if (i==0){
                lastCharCnt = 1;
                newStr[j] = str[i];
                j++;
            }
            else if (str[i] == str[i-1]) {
                lastCharCnt++;
            }
            else {
                j = j + copyNum(newStr + j, lastCharCnt);
                lastCharCnt = 1;
                newStr[j] = str[i];
                j = j + 1;
            }
        }
        j = j + copyNum(newStr + j, lastCharCnt);
        newStr[j] = 0;
    }

    return newStr;
}

int main() {
    char *compStr = compress("dev");
    char *compStr2 = compress("dddddeeevvvvvv");

    cout<<compStr<<endl;
    cout<<compStr2<<endl;

    delete [] compStr;
    delete [] compStr2;
}
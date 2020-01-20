#include <iostream>
#include <string.h>

using namespace std;

int countSpace(char *s) {
    int cnt = 0;
    if (!s) {
        return 0;
    }

    for (int i=0; s[i]; i++) {
        if (s[i] == ' ') {
            cnt++;
        }
    }
    return cnt;
}

int replaceSpace(char *s, int oldLen) {
    int spaceCnt = countSpace(s);
    int newLen = oldLen - spaceCnt + spaceCnt*3;
    
    s[newLen] = 0;
    for (int src = oldLen-1, dest = newLen - 1; src >= 0; src--) {
        if (s[src] == ' ') {
            s[dest] = '0';
            s[dest -1] = '2';
            s[dest - 2] = '%';
            dest = dest - 3;
        }
        else {
            s[dest] = s[src];
            dest--;
        }
    }

    return newLen;
}

int main() {
    char s[500] = "Mr. Devendra Agarwal";
    int newLen = replaceSpace(s, strlen(s));
    cout << s << " ==> " << newLen;

    return 0;
}
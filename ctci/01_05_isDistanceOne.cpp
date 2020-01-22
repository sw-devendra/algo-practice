#include <iostream>

using namespace std;

bool isEditOne(string s1, string s2) {
    if (s1.length() != s2.length())
        return false;

    bool editDone = false;

    for (int i =0 ; i< s1.length(); i++) {
        if (s1[i] == s2[i])
            continue;
        if (! editDone) {
            editDone = true;
        }
        else {
            return false;
        }
    }
    return true;
}

bool isAddOne(string s1, string s2) {
    string big;
    string small;
    if (s1.length() > s2.length()) {
        big = s1;
        small = s2;
    }
    else {
        big = s2;
        small = s1;
    }
    if ((big.length() - small.length()) != 1) {
        return false;
    }

    bool oneAdditionFound = false;
    for (int bi=0, si = 0; si < small.length();) {
        if (small[si] == big[bi]) {
            bi++;
            si++;
        }
        else {
            if (oneAdditionFound) {
                return false;
            }
            else {
                oneAdditionFound = true;
                bi++; // do not increase si as it needs to be compared with next char
            }
        }
    }
}

bool isDistOne(string s1, string s2) {
    if (isEditOne(s1, s2))
        return true;
    if (isAddOne(s1, s2))
        return true;

    return false;
}

int main() {
    cout <<isDistOne("devendra", "devendPa") <<endl;
    cout <<isDistOne("dev", "devendra") << endl;
    cout <<isDistOne("devendra", "dvendra") << endl;
    cout <<isDistOne("dvendra", "devendra") << endl;
    cout <<isDistOne("devendra","dbvbndra") <<endl;

    return 0;
}
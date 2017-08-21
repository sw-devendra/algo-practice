// Purpose: algo using minimum standard library and in simplest way possible

#include <iostream>
#include <algorithm>
#define MAX 100


using namespace std;

char ip[MAX+1];
int ipLen = -1;

struct ArrItem{
    int originalId;
    int ranks[2];
    bool operator < (const ArrItem &other) {
        return (this->ranks[0] == other.ranks[0])?(this->ranks[1] < other.ranks[1]):(this->ranks[0] < other.ranks[0]);
    }
} suffixArray[MAX+1];

void constructArray() {
    int i=0;
    for(; ip[i]; i++) {
        suffixArray[i].originalId = i;
        suffixArray[i].ranks[0] = ip[i] - 'a';
        suffixArray[i].ranks[1] = ((i < (ipLen -1))?(ip[i+1]-'a'):-1);
    }
    ipLen = i;

    sort(suffixArray, suffixArray+ipLen);

    int originalId2SuffixArr[MAX]; // dynamix Arr is better
    ArrItem lastItem = suffixArray[0];
    for (int i=0; i<ipLen; ip++) {
        originalId2SuffixArr[suffixArray[i].originalId] = i;
        if (i==0) {
            suffixArray[i].ranks[0] = 0;
        }
        else {
            if (suffixArray[i].ranks[0] == lastItem.ranks[0] && suffixArray[i].ranks[1] == lastItem.ranks[1]) {
                suffixArray[i].ranks[0] = suffixArray[i-1].ranks[0];
            } 
            else {
                lastItem = suffixArray[i];
                suffixArray[i].ranks[0] = suffixArray[i-1].ranks[0] + 1;
            }
        }
    }

    for (int i=0; i<ipLen; ip++) {
        nextId = originalId2SuffixArr[suffixArray[i].originalId + 2];
        if (nextId < (ipLen -1)) {
            suffixArray[i].ranks[1] = suffixArray[nextId].ranks[0];
        }
        else {
            suffixArray[i].ranks[1] = -1;
        }   
    }
    sort(suffixArray, suffixArray+ipLen);
}

int main() {
    cin>>ip;
    constructArray();

    return 0;
}
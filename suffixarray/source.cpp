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

// Complexity n*log(n)*log(n)
void constructArray() {

    // Ranking with two chars
    int i=0;
    for(; ip[i]; i++) {
        suffixArray[i].originalId = i;
        suffixArray[i].ranks[0] = ip[i] - 'a';
        suffixArray[i].ranks[1] = (ip[i+1]?(ip[i+1] - 'a'):-1);
    }
    ipLen = i;
    sort(suffixArray, suffixArray + ipLen);

    int *originalId2SuffixArr = new int[MAX + 1]; // To maintain mapping from origial Id to current index in suffix array
    
    for(int k=4; k<2*ipLen; k = k*2) {
        // fill Rank # 1
        ArrItem lastItem = suffixArray[0];
        suffixArray[0].ranks[0] = 0; // first rank
        originalId2SuffixArr[suffixArray[0].originalId] = 0;

        for(int i=1; i<ipLen; i++) {
            if (lastItem.ranks[0] == suffixArray[i].ranks[0] 
                && lastItem.ranks[1] == suffixArray[i].ranks[1] ) {
                    suffixArray[i].ranks[0] = suffixArray[i-1].ranks[0];
                }
            else {
                    lastItem = suffixArray[i];
                    suffixArray[i].ranks[0] = suffixArray[i-1].ranks[0] + 1;
                }
            originalId2SuffixArr[suffixArray[i].originalId] = i;
        }

        // fill rank # 2
        int shift = k/2;
        for (int i=0; i<ipLen; i++) {
            int nextSuffixId = suffixArray[i].originalId + shift;
            if (nextSuffixId <ipLen) {
                suffixArray[i].ranks[1] = suffixArray[originalId2SuffixArr[nextSuffixId]].ranks[0];
            }
            else {
                suffixArray[i].ranks[1] = -1;
            }
        }
        // sort based on latest ranks
        sort(suffixArray, suffixArray + ipLen);
    }
    delete []originalId2SuffixArr; 
}



int main() {
    cin>>ip;
    constructArray();

    // test if the suffixes look sorted
    for (int i=0; i<ipLen; i++) {
        cout<<(ip + suffixArray[i].originalId)<<endl;
    }

    return 0;
}
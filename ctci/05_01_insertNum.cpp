#include <iostream>
#include <bitset>

using namespace std;

// Insert M into N at i to jth bit (it's not literally insert but merge)
bool insert(int N, int M, int sizeM, int i, int j, int &res)
{
    // ensure right size
    if (sizeM > ((j - i) + 1)) {
        return false;
    }
    
    // assuming that M is 0 padded (all the bits before last sizeM bits in M are 0s)

    int cnt = j - i;
    int mask = ((((-1) << cnt) + 1) << i ) - 1; // Need to generate 11111000001111 kind mask where M will be inserted at the place of 0s
    N = N & mask; // i through j bits are 0s in N now
    res = N | (M << i);
    return true;
}
int main() {
    bitset<sizeof(int)*8> k(-1); // test
    int N = 0b1010101010101111; // any random num
    int M = 0b11101;
    int res = 0;
    if (insert(N,M,5, 5, 9, res)) {
        bitset<16> resBit(res);
        cout<< resBit; // expectation => 1010101110101111
    }
    else {
        cout <<"Error!";
    }
    return 0;
}
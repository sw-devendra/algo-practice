#include <iostream>
#include <vector> 
using namespace std;

class Solution {
public:
    /**
     * @param nums: a list of integer
     * @return: return a integer, denote  the maximum number of consecutive 1s
     */
    int findMaxConsecutiveOnes(vector<int> &nums) {
        // write your code here
        int current1Start= -1, current, s=-1,max=-1,i=-1;
        for (i=0; i<nums.size(); i++) {
            if (i==0) {
                s = 0;
            }
            if (nums[i]==1) {
                if (current1Start == -1) {
                    current1Start = i;
                }
            }
            else {
                // update max
                current = i -s;
                if (current > max) {
                    max = current;
                }
                // update s
                if (current1Start != -1) {
                    s = current1Start;
                }
                else {
                    s = i;
                }
                current1Start = -1;
            }
        }
        current = i-s; // assuming that there is at least one element in the vector so s is not -1
        if (max < current) {
            max = current;
        }
        return max;
    }
};

int main() {
    Solution s;
    vector<int> v = {0,1,1,0,1,1,1,0,0,1,0,1,0,1,1,1,1,1,0,1};
    cout<<s.findMaxConsecutiveOnes(v);
    return 0;
}
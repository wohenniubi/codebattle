
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    //Runtime: 20 ms, faster than 56.68%
    //Memory Usage: 19.7 MB, less than 48.59%
    int majorityElement(vector<int>& nums) {
        // moore voting算法，假定一个数是出现次数超过n/2的那个数，用一个计数器来统计它
        // 然后每次取走一对不相同的数，则最后剩下的那一个为所求，或者是某一个n/2的数
        int cnt = 0, rtn = INT_MAX;
        
        // 就这么简单，背下来吧
        for (auto &num : nums) {
            if (cnt == 0)
                rtn = num;//首先要初始化一个值为目标
            
            // 然后通过统计数字出现的次数来进行去除操作，而不是真正的pop_back
            if (rtn == num)
                cnt++;
            else
                cnt--;
        }
        
        return rtn;
    }
};

int main(int argc, const char * argv[]) {
    Solution gua;
    int rtn;
    vector<int> nums;
    
    rtn = gua.majorityElement(nums = {3,2,3});
    cout << "expect value = 3, actual value = " << rtn << endl;

    rtn = gua.majorityElement(nums = {2,2,1,1,1,2,2});
    cout << "expect value = 2, actual value = " << rtn << endl;

    return 0;
}

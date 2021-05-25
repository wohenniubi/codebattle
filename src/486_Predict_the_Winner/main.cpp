
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
public:
    //Runtime: 0 ms, faster than 100.00%
    //Memory Usage: 8.7 MB, less than 10.16%
    // 都是希望这个diff值最大，这样的框架里面谁是player1已经没有影响力
    int minMaxDiff(vector<int> &nums, int bgn, int end, unordered_map<int,int> &memo) {
        // TODO返回条件
        if (bgn == end)
            return nums[bgn];
        
        int index = bgn*100 + end;// bgn和end都属于[0,20]
        if (memo.count(index))
            return memo[index];
        
        // 然后就是两个选择，bgn或者end, minMaxDiff获得的是对方得到的diff最大值，减去这个diff才能把自己选择的数据sum在一起
        int lhs = nums[bgn] - minMaxDiff(nums, bgn+1, end, memo);
        
        int rhs = nums[end] - minMaxDiff(nums, bgn, end-1, memo);
        memo[index] = max(lhs, rhs);
        return max(lhs, rhs);
    }
    
    bool PredictTheWinner(vector<int>& nums) {
        // 需要使用的状态包括起始和结束index，sum的差值（这样可以只统计一个数），是否是player1
        unordered_map<int,int> memo;// 会出现重复计算，所以需要用memo
        int diff = minMaxDiff(nums, 0, nums.size()-1, memo);
        return diff >= 0;
    }
};

int main(int argc, const char * argv[]) {
    Solution gua;
    bool rtn;
    vector<int> nums;
    
    rtn = gua.PredictTheWinner(nums={1,5,2});
    cout << "expect value = 0, actual value = " << rtn << endl;

    rtn = gua.PredictTheWinner(nums={1,5,233,7});
    cout << "expect value = 1, actual value = " << rtn << endl;
    return 0;
}

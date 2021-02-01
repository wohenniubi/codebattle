
#include <iostream>
#include <queue>

using namespace std;

class Solution {
public:
    //Runtime: 564 ms, faster than 30.14%
    //Memory Usage: 118.7 MB, less than 52.18%
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        // 回想起这道题了，需要使用一个单调的队列，每次也要pop
        deque<int> q;
        vector<int> rtn;
        // 需要存index
        // for (int val : nums) {
        int cnt = 0;
        for (int i = 0; i < nums.size(); ++i) {
            // 想了一下，不能pop等号，要不没数据了
            // 然后另一个难点是如何保证在窗的左边界时输出最大值，即使存了index，也可能被pop
            while (q.size() && nums[q.back()] < nums[i]) {
                q.pop_back();// 留着小的数对于最大值没有帮助
            }
            // 跳出while循环表明q为空或者q里面的数比较大
            q.push_back(i);
            cnt++;
            if (cnt < k) continue;//k之前不产生数据
            
            // 滑动窗开始产生数据，此时q里面肯定是有数据的
            rtn.push_back(nums[q.front()]);
            // 在开始加入下一个数的时候pop掉过时的数据
            if (i - q.front() + 1 == k) q.pop_front();
        }
        return rtn;
    }
};

ostream & operator<< (ostream &os, vector<int> &rtn) {
    os << "[";
    for (auto val : rtn) os << val << ",";
    os << "]";
    return os;
}

int main(int argc, const char * argv[]) {
    Solution gua;
    vector<int> rtn, nums, exp;
    int k;
    rtn = gua.maxSlidingWindow(nums={1,3,-1,-3,5,3,6,7}, k = 3);
    exp = {3,3,5,5,6,7};
    cout << "expect result = " << exp << ", actual result = " << rtn << endl;

    rtn = gua.maxSlidingWindow(nums={1}, k = 1);
    exp = {1};
    cout << "expect result = " << exp << ", actual result = " << rtn << endl;

    rtn = gua.maxSlidingWindow(nums={1, -1}, k = 1);
    exp = {1, -1};
    cout << "expect result = " << exp << ", actual result = " << rtn << endl;

    rtn = gua.maxSlidingWindow(nums={4, -2}, k = 2);
    exp = {4};
    cout << "expect result = " << exp << ", actual result = " << rtn << endl;
    return 0;
}

#include <iostream>
#include <set>
#include <map>
#include <queue>
#include <vector>

using namespace std;

// 基本原理是需要一个滑动窗一样的array结构，同时能够尽快(例如：O(1)或者O(logn)的复杂度)告知最小值和最大值
class Solution {
public:
    // 使用multiset的方法要特别注意erase的操作，不能是erase(val)啊，要遭
    //Runtime: 500 ms, faster than 29.24% .
    //Memory Usage: 78.9 MB, less than 5.02%
    int longestSubarray1(vector<int>& nums, int limit) {
        int rtn = 0; // size of the longest subarray;
        if (nums.empty() || limit < 0) return rtn;// 绝对值不会小于0
        
        multiset<int> longest{{nums[0]}};// 初始化
        rtn = 1;//一个元素肯定是满足情况的，此时diff(max - min) = 0
        int bgn = 0;// longest 集合开始的pos
        for (int i = 1; i < nums.size(); ++i) {
            int num = nums[i];
            // 如果新加入的nums[i]让集合超过limit，则更新集合
            while (longest.size()
                   && (abs(*(longest.begin())-num) > limit || abs(*(longest.rbegin())-num) > limit)) {
                   //&& (abs(longest.front()-nums[i]) > limit || abs(longest.back()-nums[i]) > limit)) {
                   // 大意了，multiset没有front()和back()
                //longest.erase(nums[bgn++]);// 傻了吧，erase(value)的话删除的是所有等于value的成员...
                //longest.erase(longest.begin());// 不能总删除第一个，nums={2,2,2,4,4,2,5,5,5,5,5,2}, limit=2
                longest.erase(longest.equal_range(nums[bgn++]).first);// 还是要erase(iter)，而且只删一个
            }
            // 跳出while循环表明新加入的nums[i]可以满足limit的限制，那就往死里加
            longest.insert(num);
            
            //rtn = max(rtn, (i-bgn)+1);// 怎么这么大意，缺少加入longest之后要更新rtn...
            //rtn = max(rtn, (int)longest.size()); //由于去掉了bgn，所以直接用集合的size来更新
            rtn = max(rtn, (i-bgn)+1);
        }
        
        return rtn;
    }
    
    //Runtime: 332 ms, faster than 68.52%
    //Memory Usage: 62.8 MB, less than 46.51%
    // 自己改出来的，采用map的做法，时间复杂度为O(nlogn)。注意要处理val的计数次数，等于0之后一定要清除掉，否则begin()有问题
    int longestSubarray2(vector<int>& nums, int limit) {
        int rtn = 0;
        if (nums.empty() || limit < 0) return rtn;
        
        map<int,int> longest{{nums[0],1}};//保存这个满足条件的集合
        int bgn = 0;//记录这个集合开始的位置是0
        rtn = 1;
        for (int i = 1; i < nums.size(); ++i) {
            int num = nums[i];
            while (longest.size()
                   && (abs(longest.begin()->first - num)>limit || abs(longest.rbegin()->first - num)>limit)) {
                // 不能每次删除map里面的第一个，这样会删除后面的一些成员，导致nums={2,2,2,4,4,2,5,5,5,5,5,2}, limit=2失败
                // if (--(longest.begin()->second) == 0) {
                //     longest.erase(longest.begin());
                // }
                if (--longest[nums[bgn]] == 0) {
                    longest.erase(nums[bgn]);
                }
                bgn++;// 移动一下集合的开始位置
            }
            // 跳出循环表明可以满足limit的限制，因此加入集合
            longest[num]++;
            rtn = max(rtn, i-bgn+1);
        }
        
        return rtn;
    }
    
    // 网上做法：使用monotonic queue的方法，时间复杂度是O(n)，不过需要两个queue，参考leetcode 716（1245）
    //Runtime: 248 ms, faster than 76.49%
    //Memory Usage: 52.3 MB, less than 64.70%
    int longestSubarray(vector<int>& nums, int limit) {
        deque<int> max_q, min_q;
        int rtn = 0, l = 0;
        for (int r = 0; r < nums.size(); ++r) {
            // 首先维护最大queue和最小queue; 相当于把queue里面数据从后面挤出来
            while (max_q.size() && nums[r] > max_q.back())
                max_q.pop_back();
            while (min_q.size() && nums[r] < min_q.back())
                min_q.pop_back();
            // 挤出来之后至少还要塞回去一个呀
            max_q.push_back(nums[r]);
            min_q.push_back(nums[r]);
            
            // 现在开始维护满足limit条件的subarray, 即考量加入nums[i]之后是否移动滑动窗的最左边
            // 之所以只需要调整左边界就OK，因为subarray限制下，只能去掉左边界才有机会更新subarray
            while (abs(max_q.front()- min_q.front()) > limit) {
                // 不是移除nums[r]哟，要移除最左边的值的时候; 记得维护最大和最小的queue
                if (max_q.front() == nums[l]) max_q.pop_front();
                if (min_q.front() == nums[l]) min_q.pop_front();
                l++;
            }
            rtn = max(rtn, r-l + 1);//所有的情况处理结束之后，维护subarray的长度
        }
        
        return rtn;
    }
};

int main(int argc, const char * argv[]) {
    // insert code here...
    Solution gua;
    int rtn, limit;
    vector<int> nums;
    rtn = gua.longestSubarray(nums={2,2,2,4,4,2,5,5,5,5,5,2}, limit=2);
    cout << "expect value = 6, actual value = " << rtn << endl;
    
    rtn = gua.longestSubarray(nums={4,2,2,2,4,4,2,2}, limit=0);
    cout << "expect value = 3, actual value = " << rtn << endl;
    
    rtn = gua.longestSubarray(nums={8,2,4,7}, limit=4);
    cout << "expect value = 2, actual value = " << rtn << endl;
    
    return 0;
}

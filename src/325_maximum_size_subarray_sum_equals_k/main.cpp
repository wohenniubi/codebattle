
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution
{
public:
    // 基本解法是使用累加数组和哈希表存累加数组的值, 由于累加数组任意两个元素的差值
    // 对应就是某个subarray的sum. 那么求subarray = k, 就是等于求 a-b = k;
    // 于是哈希表只需要存b, 然后每次在表里面用a-k去查询就好
    
    // 方法1:
    int maxSubArrayLen1(vector<int> &nums, int k) {
        if (nums.empty()) return 0;
        int rst = 0;
        unordered_map<int, vector<int>> helper;
        helper[nums[0]].push_back(0);
        vector<int> sums = nums;
        // 构建累加数组nums, 同时构建哈希表, 存累加数组的值, 由于可能出现重复,
        // 所以content用vector, 每次把一个index都append到后面
        for (int i = 1; i < nums.size(); ++i) {
            sums[i] += sums[i-1];
            helper[sums[i]].push_back(i);
        }
        
        // 遍历哈希表, 注意哈希表的auto是个iterator
        for (auto it : helper) {
            if (it.first == k)
                rst = max(rst, it.second.back()+1);
            else if (helper.find(it.first - k) != helper.end())
                rst = max(rst, it.second.back() - helper[it.first - k][0]);
        }
        return rst;
    }
    
    // 方法2: 与方法1思路一致, 简单改进: 其实并不需要用vector来存所有的index,
    // 只需要存一个index就好, 原因是本题需要找到最长的subarray, 而累加数组是
    // 从一个方向顺序计算的, 所以 (1) 对于某个完整累加数组就等于给定k值的情况,
    // 第一次出现的index与当前i构成的subarray必定是最长的, 所以(1)这种情况下
    // 不需要更新index; (2) 对于由两个累加数组的成员构成k值的情况, 也是由找到的
    // 最早出现的那个index与i组成的subarray必定是最长的, 所以(1)&(2)的情况下,
    // 就存一个index就OK;
    // 另外, 其实并不需要用具体的累加数组nums, 只需要一个临时变量就OK了
    int maxSubArrayLen2(vector<int> &nums, int k) {
        if (nums.empty()) return 0;
        unordered_map<int, int> helper {{0,-1}};
        int sum = 0, rst = 0;
        for (int i = 0; i < nums.size(); ++i) {
            sum += nums[i];
            int tmp = sum - k;
            if (helper.count(tmp)) {
                rst = max(rst, i - helper[tmp]);
            } else {
                //                helper[sum] = i;
                if (!helper.count(sum)) helper[sum] = i;
            }
        }
        return rst;
    }
   
    // Runtime: 156 ms, faster than 60.59%
    // Memory Usage: 50.8 MB, less than 92.27%
    int maxSubArrayLen(vector<int>& nums, int k) {
        // 要用到哈希表和前缀和
        unordered_map<int,int> memo{{0, -1}};// 作为前缀和，保存index

        int sum = 0, rtn = 0;
        for (int i = 0; i < nums.size(); ++i) {
            sum += nums[i];

            auto iter = memo.find(sum - k);
            if (iter != end(memo)) {
                rtn = max(rtn, i - iter->second);//这里就不加1了
            }
            //memo[sum] = i;
            // 注意这里存入的是sum, 所以要再次判断一下, 因为保留了旧的index, 才能获得最长的subarray
            if (!memo.count(sum)) memo[sum] = i;
        }

        return rtn;
    }

    int maxSubArrayLen0(vector<int> &nums, int k) {
        unordered_map<int, int> helper;
        int sum = 0, rst = 0;
//        for (int i = 0; i < nums.size(); ++i) {
//            sum += nums[i];
//            int tmp = sum - k;
//            // 分两种情况讨论, (1)当某个累加数组等于给定k时, 就是这个累加数组的长度
//            if (sum == k) {
//                rst = i+1;// 因为是从左到右顺序处理的i++, 所以i必定比之前的rst大
//                // 故不再需要rst = max(rst, i+1); i+1是因为index是0-base, 算长度时要加1
//            } else {
//                // (2)当累加数组不等于给定k时, 需要查找与k的差值是否存在于哈希表中;
//                // 如果在, 则计算subarrya的长度, 至于长度是否+1, 举个例子就可以推算出来
//                if (helper.count(tmp))
//                    rst = max(rst, i- helper[tmp]);
//            }
//            // 最后始终要把累加数组存到哈希表里面去, 而不是tmp
//            if (!helper.count(sum))
//                helper[sum] = i;
//        }
        
        for (int i = 0; i < nums.size(); ++i) {
            sum += nums[i];
            if (sum == k) rst = i + 1;
            else if (helper.count(sum - k)) rst = max(rst, i - helper[sum - k]);
            if (!helper.count(sum)) helper[sum] = i;
        }
        
        return rst;
    }
};

int main() {
    int rst, k;
    Solution gua;
    vector<int> nums1 = {-1, 1, 5, -2, 3};
    rst = gua.maxSubArrayLen(nums1, k=3);
    cout << "expect rst = 4, actual rst = " << rst << endl;
    
    vector<int> nums2 = {-2, -1, 2, 1};
    rst = gua.maxSubArrayLen(nums2, k=1);
    cout << "expect rst = 2, actual rst = " << rst << endl;
    
    vector<int> nums3 = {1, 0, -1};
    rst = gua.maxSubArrayLen(nums3, k=-1);
    cout << "expect rst = 2, actual rst = " << rst << endl;
    
    return 0;
}

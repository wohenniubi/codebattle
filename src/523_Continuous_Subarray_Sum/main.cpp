#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    // Runtime: 188 ms, faster than 35.20%
    // Memory Usage: 96 MB, less than 93.59%
    bool checkSubarraySum(vector<int>& nums, int k) {
        // 属于典型的使用前缀和再加STL结构的题
        // 怎么把前缀和与取模联系起来呢，想一想ai之前的前缀和可以表示为
        // A1 = a0+a1+...ai = kN1 + q1
        // 而另一个aj之前的前缀和可以表示为
        // A2 = a0+a1+...ai+ai+1 + ... +aj = kN2 + q2
        // 两者之差变成A2-A1 = ai+1 + ... aj = k(N2-N1) + (q2-q1)
        // 注意这里的ai+1 + ... aj就是subarray的和，要让它可以被k整除，就要求q2-q1为0
        // 或者说，计算A2的余数q2时，如果可以在历史记录中找到一个相同的余数，那么A2和A1之间的元素就构成符合模k条件的subarray
        //
        // 为了保证subarray的长度超过2，因此还需要记录下那个余数的index，所以需要哈希表
        //unordered_map<int, int> memo{{0,0}};// TODO初始化
        // 如果初始化为{0,0}，后续使用i - iter->second + 1 >= 2，会在{1,0}k=2这个例子失败，因此要改为
        unordered_map<int, int> memo{{0,-1}};// 搭配后续i - iter->second + 1 > 2

        int sum = 0;//0 <= sum(nums[i]) <= 231 - 1 所以一个int够用
        for (int i = 0; i < nums.size(); ++i) {
            sum += nums[i];
            // 计算ai这个前缀和的余数，因为k>0，所以不用特殊处理
            int q = sum % k;// 因为nums[i]是非负数，所以sum必定为非负数，取模后q必定非负
            auto iter = memo.find(q);

            if (iter == memo.end()) {
                memo[q] = i;// 没有的话直接加入memo
            } else {
                // 如果找到这个余数的话，比较subarray的长度是否符合条件
                // 此时也说明初始化时应该放入一个0，因为万一出现q为0的情况
                //if (i - iter->second + 1 >= 2) {
                if (i - iter->second + 1 > 2) { // 这里需要搭配memo{{0,-1}}
                    return true;
                }
                // 如果长度不大于2，那么继续执行，先前的index也不要修改，因为留着最早的index，更能够找到符合条件的subarray
            }
        }

        return false;// 如果所有数处理完没有返回，只可能是没有满足条件的subarray
    }
};

int main() {
  Solution gua;
  vector<int> nums;
  int k;
  bool rtn;

  rtn = gua.checkSubarraySum(nums = {1, 0}, k = 2);
  cout << "expect value = 0, actual value = " << rtn << endl;
  
  rtn = gua.checkSubarraySum(nums = {23, 2, 4, 6, 7}, k = 6);
  cout << "expect value = 1, actual value = " << rtn << endl;
  
  rtn = gua.checkSubarraySum(nums = {23, 2, 6, 4, 7}, k = 6);
  cout << "expect value = 1, actual value = " << rtn << endl;
  
  rtn = gua.checkSubarraySum(nums = {23, 2, 6, 4, 7}, k = 13);
  cout << "expect value = 0, actual value = " << rtn << endl;
  return 0;
}


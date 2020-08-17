#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
public:
    //    vector<int> memo (101,-1);//减少重复计算；大意了，不能在class里面这样初始化非static变量
    vector<int> memo;
    int cntGpairs(int n) {
        if (n < 2) {
            return memo[n] = 0;
        }
        if (memo[n]) return memo[n];
        
        int rtn = (cntGpairs(n-1)+n-1);
        return memo[n] = rtn;
    }

    int numIdenticalPairs(vector<int>& nums) {
        unordered_map<int,int> helper;
        
        // 首先遍历一遍nums提取所有值相等的num
        for (auto & num : nums) {
            helper[num]++;
        }
        
        // 然后对每个group进行处理
        int gnum = 0;
        memo = vector<int>(101);
        for (auto [key, value] : helper) {
            if (value < 2) continue;
            
            // 一旦找到一个超过1的group，计算其good pairs个数
            gnum += cntGpairs(value);
        }
        return gnum;
    }
    
};

// 网上的第二种方法；可以参考一下
// 空间复杂度为O(1)，就是每次将后面所有的数与当前数进行比较
// 时间复杂度为O(n2)
class Solution2 {
public:
    int numIdenticalPairs(vector<int>& nums) {
        int count = 0;
        for (int i=0; i<nums.size()-1; i++){
            for (int j=i+1; j<nums.size(); j++){
                if (nums[i] == nums[j])
                    count++;
            }
        }
        return count;
    }
};

int main(int argc, const char * argv[]) {
    Solution gua;
    int rtn;
    vector<int> nums;
    rtn = gua.numIdenticalPairs(nums={1,2,3,1,1,3});
    std::cout << "expect value = 4, actual value = " << rtn << std::endl;
    return 0;
}



#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    //Runtime: 408 ms, faster than 11.19%
    //Memory Usage: 24.3 MB, less than 84.13%
    int fourSumCount(vector<int>& nums1, vector<int>& nums2, vector<int>& nums3, vector<int>& nums4) {
        // 看了下解答，自己再试一下吧
        // 采用哈希表保存两个数的值，此时复杂度为O(n^2)，然后再计算另外两个数的sum，利用哈希表查找是否存在-sum
        // unordered_map<int, vector<pair<int,int>>> sum12;
        unordered_map<int, int> sum12;// 因为只需要统计个数，所以不需要存具体的pair信息
        
        int n = nums1.size();
        
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                int sum = nums1[i] + nums2[j];
                // sum12[sum].push_back({i, j});
                sum12[sum]++;
            }
        }
        
        int rtn = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                // int sum = nums3[i] + nums3[j];//怎么这么大意！！！
                int sum = nums3[i] + nums4[j];
                if (sum12.count(-sum) == 0) continue;
                
                // 此时说明sum12[-sum]中的所有值，都可以与当前的nums3[i]和nums4[j]构成0
                rtn += sum12[-sum];
            }
        }
        return rtn;
    }
};

int main(int argc, const char * argv[]) {
    Solution gua;
    int rtn;
    vector<int> nums1, nums2, nums3, nums4;
    
    rtn = gua.fourSumCount(nums1={1}, nums2={-1}, nums3={0}, nums4={1});
    cout << "expect value = 0, actual value = " << rtn << endl;
    
    rtn = gua.fourSumCount(nums1={1,2}, nums2={-2,-1}, nums3={-1,2}, nums4={0,2});
    cout << "expect value = 2, actual value = " << rtn << endl;
    return 0;
}

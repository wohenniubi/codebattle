
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    //Runtime: 8 ms, faster than 82.81%
    //Memory Usage: 10.1 MB, less than 39.08%
    vector<int> singleNumber(vector<int>& nums) {
        // 根本想不到这种做法
        // 首先获得x和y的异或值
        int xory = 0;
        for (auto &num : nums)
            xory ^= num;
        
        // 现在获得一个分离因子，借助它可以把原始数据的x和y分配到不同的两组
        // 然后每一组就只有一个不同的值，就搞定了
        // int factor = xory & (~(xory - 1));// 这里的~是按位取反
        // [1,1,0,-2147483648]这个值怎么处理
        long long factor = xory;
        factor &= ~(factor-1);
        
        int x = 0;
        for (auto &num : nums) {
            if (num & factor) {
                x ^= num;//这里通过与factor进行与操作，可以把x和y拆分到不同的分组，咱们固定选任意一个分组
            }
        }
        int y = x ^ xory;
        return {x,y};
    }
};

int main(int argc, const char * argv[]) {
    Solution gua;
    vector<int> rtn, nums;
    rtn = gua.singleNumber(nums = {1,1,0,-2147483648});
    cout << "expect value = [-2147483648,0], actual value = [" << rtn[0] << "," << rtn[1] << "]" << endl;

    rtn = gua.singleNumber(nums = {1,2,1,3,2,5});
    cout << "expect value = [3,5], actual value = [" << rtn[0] << "," << rtn[1] << "]" << endl;

    rtn = gua.singleNumber(nums = {1,5});
    cout << "expect value = [5,1], actual value = [" << rtn[0] << "," << rtn[1] << "]" << endl;

    return 0;
}

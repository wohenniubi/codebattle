#include <iostream>
#include <vector>

using namespace std;

//Runtime: 116 ms, faster than 90.03%
//Memory Usage: 29.5 MB, less than 40.55%
class Solution {
public:
    // 本打算使用dp做的，搞不定；查资料发现是Math，好吧，服了，权当复习一下gcd了
    
    // 这里的问题转化非常的tricky，大致是这样理解，计算nums[i]与0~i-1所有数的最大公约数的gcd
    // 几个heuristic是：1) 当gcd等于1时，Bezout公式是充要条件，此时必定可以凑出ax+by=1；
    // 2) 集合越大，gcd越小；因此我们会尽量将集合扩大，这样更容易找到gcd=1的情况

    bool isGoodArray(vector<int>& nums) {
        int size = nums.size();
        
        //if (size < 2) return false;// 大意了，有个case是[1] -> true
        if (size < 1) return false;
        
        int g = nums[0];
        for (int i = 1; i < nums.size(); ++i) {
            g = gcd(g, nums[i]);
        }
        return g == 1;
    }
    
    // 以下gcd写法最终都会让入参a小于b，如果a大于b，第一次gcd相当于是swap(a,b)
    int gcd(int a, int b) {
        if (a == 0)
            return b;
        return gcd(b%a, a);
    }
};

int main(int argc, const char * argv[]) {
    Solution gua;
    bool rtn;
    vector<int> nums;
    
    rtn = gua.isGoodArray(nums={12,5,7,23});
    cout << "expect value = 1, actual value = " << rtn << endl;
    
    rtn = gua.isGoodArray(nums={29,6,10});
    cout << "expect value = 1, actual value = " << rtn << endl;

    rtn = gua.isGoodArray(nums={3,6});
    cout << "expect value = 0, actual value = " << rtn << endl;
    
    rtn = gua.isGoodArray(nums={1});
    cout << "expect value = 1, actual value = " << rtn << endl;
    return 0;
}



#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int maxArea(vector<int>& height) {
        // 貌似数组+STL的做法适用于LC42题trapping rain，这道题还是左右向中间压缩
        
        int lhs = 0, rhs = height.size()-1;
        int rtn = 0;// 初始化为0，没毛病
        while (lhs < rhs) { // lhs == rhs面积为0，没有意义
            int maxh = min(height[lhs], height[rhs]);
            int len = rhs - lhs;
            rtn = max(rtn, maxh*len);
            
            // 然后修改lhs和rhs
            if (height[lhs] > height[rhs]) {
                --rhs;// 此时压缩右边才会有可能找到更大的area
            } else {
                ++lhs;// 反之或者相等的时候，固定都移动左边的位置
            }
        }
        
        return rtn;
    }
};

int main(int argc, const char * argv[]) {
    Solution gua;
    int rtn;
    vector<int> height;
    
    rtn = gua.maxArea(height = {});
    cout << "expect value = 49, actual value = " << rtn << endl;
    return 0;
}

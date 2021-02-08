
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    bool canEatAll(vector<int> &piles, int H, int K) {
        int cnt = 0;
        for (auto val : piles) {
            cnt += (val/K + (val%K != 0));
        }
        return cnt <= H;
    }
    
    //Runtime: 52 ms, faster than 86.45%
    //Memory Usage: 18.7 MB, less than 96.50%
    int minEatingSpeed(vector<int>& piles, int H) {
        int rhs = *max_element(begin(piles), end(piles));
        // 先给出个trivial解，当H和piles的size相等时，想吃完所有的香蕉，只能取最大的那个值
        if (H == piles.size()) return rhs;
        
        //int sum = accumulate(begin(piles), end(piles), 0);
        int lhs = 1;// [1,2,3], H = 3, Kmax=3, H=4, K=2, H=6, Kmin=1
        
        // 然后是H大于piles.size()的情况，二分处理，符合最左边边界rhs的模版
        rhs++;
        while (lhs < rhs) {
            int mid = lhs + (rhs-lhs)/2;
            // 检查mid是否可以搞定，如果可以搞定，需要修改左右边界
            if (canEatAll(piles, H, mid)) {
                rhs = mid;
            } else {
                lhs = mid+1;
            }
        }
        // 跳出while循环时，返回lhs-1
        //return lhs-1; 下次先试一试lhs，不行再-1
        return lhs;
    }
};

int main(int argc, const char * argv[]) {
    Solution gua;
    int rtn, H;
    vector<int> piles;
    rtn = gua.minEatingSpeed(piles={3,6,7,11}, H=8);
    cout << "expect result = 4, actual result = " << rtn << endl;
    
    rtn = gua.minEatingSpeed(piles = {30,11,23,4,20}, H = 5);
    cout << "expect result = 30, actual result = " << rtn << endl;
    
    rtn = gua.minEatingSpeed(piles = {30,11,23,4,20}, H = 6);
    cout << "expect result = 23, actual result = " << rtn << endl;
    
    return 0;
}


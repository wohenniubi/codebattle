
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    //Runtime: 16 ms, faster than 91.28%
    //Memory Usage: 17.8 MB, less than 31.00%
    int candy(vector<int>& ratings) {
        // 大方向对了，是greedy做法，利用了单调栈，然后左右操作;
        int size = ratings.size();
        if (size < 2)
            return size;

        vector<int> memo = vector<int>(size,1); // 先给每个人一个糖，然后从左到右找递增序列
        for (int i = 1; i < size; ++i) {
            if (ratings[i] > ratings[i-1]) {
                memo[i] = memo[i-1]+1;
            }
            // 对于等于和小于的情况，就还是为1，不操作
        }
        
        int rtn = memo.back();
        int prev = rtn;
        // 再从右往左查找递增序列，使用变量prev，省略了一个array
        for (int i = size-2; i >= 0; --i) {
            if (ratings[i] > ratings[i+1]) {
                prev += 1;
            } else {
                prev = 1;// 又从prev = 1开始计数
            }
            rtn += max(memo[i], prev);//在从左到右和从右到左的序列里面找最大值
        }
        
        return rtn;
    }
};

int main(int argc, const char * argv[]) {
    Solution gua;
    int rtn;
    vector<int> ratings;
    rtn = gua.candy(ratings = {12,4,6,8,7,2,3,6,9,7,1});
    cout << "expect value = 23, actual value = " << rtn << endl;

    rtn = gua.candy(ratings = {1,3,2,2,1});
    cout << "expect value = 7, actual value = " << rtn << endl;
    
    rtn = gua.candy(ratings = {1,0,2});
    cout << "expect value = 5, actual value = " << rtn << endl;
    
    rtn = gua.candy(ratings = {1,2,2});
    cout << "expect value = 4, actual value = " << rtn << endl;

    return 0;
}

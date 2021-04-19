
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

class Solution {
public:
    //Runtime: 0 ms, faster than 100.00%
    //Memory Usage: 6.1 MB, less than 6.61%

    // 这里状态只需要pos就够了，mult和k是用于条件控制
    void backtrack(string &s, string &rtn, int pos, int mult, int k) {
        // 返回条件TODO
        if (!pos)
            return;
        
        int size = mult/pos;// 得到在当前这一级，每一个数字管理多少规模
        // 例如n=3, mult=6，那么在这一级，每个数字管理2个子数组
        
        vector<int> nums(pos, size);
        for (int i = 1; i < pos; ++i) {
            nums[i] = nums[i-1] + size;
        }
        
        auto iter = lower_bound(begin(nums), end(nums), k); // 一会儿来看是不是lower_bound
        int num = distance(begin(nums), iter); // 用于得到当前位置是什么数字，0-index
        
        // 需要让去掉某个位置之后的剩下部分升序，即让选中的那个字符与其前面的部分进行交换
        int bias = s.size()-pos; // 例如：让[1,2,3,4,5]中的4被选中之后变成[4,1,2,3,5]
        rotate(s.begin()+ bias, s.begin()+ bias + num, s.begin()+ bias + num+1);
        //rtn.push_back('1'+num);
        
        k -= num*size; // 然后减少k值，
        backtrack(s, rtn, pos-1, size, k); // 其实这种在最后的dfs操作，都可以转换为iterative
        return;
    }
    
    string getPermutation(int n, int k) {
        // 有点像是回溯算法的思路，状态由path记录，然后有一个k来控制条件，然后每次有几个选择，来吧我可以的
        string s, rtn;
        int mult = 1;
        for (int i = 0; i < n; ++i) {
            s.push_back('1'+i);
            mult *= (i + 1);
        }
        
        backtrack(s, rtn, n, mult, k);
        return s;
    }
};

int main(int argc, const char * argv[]) {
    Solution gua;
    int n, k;
    string rtn;
    rtn = gua.getPermutation(n=3, k=3);
    cout << "expect value = 213, actual value = " << rtn << endl;
    
    rtn = gua.getPermutation(n=4, k=9);
    cout << "expect value = 2314, actual value = " << rtn << endl;

    rtn = gua.getPermutation(n=3, k=1);
    cout << "expect value = 123, actual value = " << rtn << endl;
    return 0;
}

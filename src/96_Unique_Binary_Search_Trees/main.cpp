
#include <iostream>
#include <vector>
#include <functional>

using namespace std;

class Solution {
public:
    //Runtime: 0 ms, faster than 100.00%
    //Memory Usage: 5.9 MB, less than 95.36%
    int numTrees(int n) {
        // 好久没有做这道题，愣是忘记怎么做了
        //unordered_map<int,int> dict
        //由于n只有19，那么干脆不用哈希表，用二维数组
        //vector<vector<int>> dict = vector<vector<int>>(20,vector<int>(20,-1));
        vector<int> dict(20,-1);
        
        function<int(int, int)> uniqueBST = [&](int bgn, int end) -> int {
            // 返回条件TODO
            // 返回1还是返回0
            // [0,1) -> 1,
            // [0,2) -> 2 ; [0,0) * [1,2) and [0,1) * [2,2)
            // [0,3) -> 5 ; [0,0) * [1,3) and [0,1) * [2,3) and [0,2) * [3,3)
            if (bgn == end) return 1;//为了保证计算正确，令空BST为1
            if (bgn+1 == end) return 1;
            
            if (dict[end - bgn] > -1) return dict[end - bgn];
            
            int rtn = 0;
            for (int i = bgn; i < end; ++i) {
                // 以i作为中间节点，[bgn,i)为左分支，[i+1,end)为右分支
                rtn += (uniqueBST(bgn, i) * uniqueBST(i+1,end));
            }
            
            return dict[end - bgn] = rtn;//dict[bgn][end] = rtn;
        };
        return uniqueBST(0, n);
    }
};

int main(int argc, const char * argv[]) {
    // insert code here...
    Solution gua;
    int rtn, n;
    
    rtn = gua.numTrees(1);
    cout << "expect value = 1. actual value = " << rtn << endl;
    
    rtn = gua.numTrees(2);
    cout << "expect value = 2. actual value = " << rtn << endl;

    rtn = gua.numTrees(3);
    cout << "expect value = 5. actual value = " << rtn << endl;
    return 0;
}


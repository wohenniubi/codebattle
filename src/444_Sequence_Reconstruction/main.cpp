
#include <iostream>
#include <vector>

using namespace std;


class Solution {
public:
    //Runtime: 40 ms, faster than 99.55%
    //Memory Usage: 35.8 MB, less than 91.44%
    bool sequenceReconstruction(vector<int>& org, vector<vector<int>>& seqs) {
        if (seqs.empty()) return false;
        
        // 非常犀利的一道题，根本没有想到做法
        // 首先是对permutation的理解，“permutation of the integers from 1 to n”意思是包含了n个数，不缺少任何一个，且不重复
        // 因为有这样的强限制条件，因此可以用vector本身的查找属性来做
        int n = org.size();
        vector<int> memo(n+1);// 为了可以使用memo[n]
        
        for (int i = 0; i < n; ++i)
            memo[org[i]] = i+1;
        
        // 然后为了应对先后顺序，就是要利用memo中的pos
        // 对于唯一性的处理更巧妙，使用了一个flag数组，唯一性无非就是能够确定1到n这n个数里，每两个相邻数值的顺序是确定的，共有n-1组两个相邻的数
        // 我们用一个数组flag和cnt来记录，cnt初始化为n-1，每次利用seqs确定一组相邻的数字后让cnt减少1，最终如果cnt=1，则说明唯一
        vector<int> flag(n+1);//flag(n-1); 为了减少对pos的转换操作，多用几个数没关系，统一以前一个数或者后一个数表示相邻数对都可以
        int cnt = n-1;
        for (auto & seq: seqs) {
            // 现在是一个sequence
            int prev = seq[0];// 题目说了len(seq) >=1
            if (prev <= 0 || prev > n)
                return false; //说明seq里面有org没有的数字
            
            for (int i = 1; i < seq.size(); ++i) {
                int curr = seq[i];
                if (curr <= 0 || curr > n)
                    return false; //说明seq里面有org没有的数字
                
                //if (memo[prev] > memo[curr]) //为了应对org={1}, seqs={{1,1}}这种情况
                if (memo[prev] >= memo[curr])
                    return false;// 说明这个seq里面的两个数不是org中的顺序，等号考不考虑？
                
                if (!flag[prev] && memo[prev]+1 == memo[curr]) {
                    // 如果两个数据的出现顺序刚好相差1，那么这两个数字就固定了
                    --cnt;
                    flag[prev]=1;
                }
                prev = curr;// 怎么如此大意！！！
            }
        }
        return cnt == 0;
    }
};

int main(int argc, const char * argv[]) {
    Solution gua;
    bool rtn;
    vector<int> org;
    vector<vector<int>> seqs;

    rtn = gua.sequenceReconstruction(org={1}, seqs={{1,1}});// 好吧，确实没说这种情况不行
    cout << "expect value = 0, actual value = " << rtn << endl;

    rtn = gua.sequenceReconstruction(org={1}, seqs={});//题目说1 <= segs[i].length <= 10^5，这尼玛还允许{}？？
    cout << "expect value = 0, actual value = " << rtn << endl;

    rtn = gua.sequenceReconstruction(org={4,1,5,2,6,3}, seqs={{4,1,5,2}, {5,2,6,3}});
    cout << "expect value = 1, actual value = " << rtn << endl;
    return 0;
}

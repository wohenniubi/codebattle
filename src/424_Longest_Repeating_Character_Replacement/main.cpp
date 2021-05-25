
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    //Runtime: 8 ms, faster than 71.87%
    //Memory Usage: 7.1 MB, less than 28.62%
    int characterReplacement(string s, int k) {
        // 想了半天，居然是用的滑动窗搞定的。。。还是没耍够题啊
        // 基本思路是统计窗长之间的字符，选择最长的字符作为base，然后看其他字符的个数（sum-最长字符个数）是否大于k
        // 如果不大于k，则继续扩展窗的右边界；如果大于k，说明不能用k个字符替换不同的字符，那么需要减少窗长，循环操作
        int lhs = 0, rhs = 0, rtn = 0;
        vector<int> memo(26);// 仅有upper case字符；用于统计不同字符的个数还有总个数
        // int total = 0; 不需要这个值的，rhs-lhs+1就是这个窗长之内的字符个数
        
        int maxLen = 0;
        while (rhs < s.size()) {
            char cur = s[rhs];
            memo[cur -'A']++;
            // total++;
            // *(max_element(begin(memo), end(memo))); 如果实在不容易理解为什么不更新maxLen，
            // 可以把maxLen设置为*(max_element(begin(memo), end(memo)))，这样每次更新，复杂度稍有提高，O(26*n)
            maxLen = max(maxLen, memo[cur -'A']); //新晋的那个char才有可能是最长的相同字符
            while (rhs-lhs+1 - maxLen > k) {
                // 此时cover不了了，要移动左边界
                memo[s[lhs]-'A']--;
                lhs++;
                // 需不需要更新一下baseNum? 不需要。因为是寻找最长子字符串长度，
                // 如果s[lhs]的值与base相同，比如：|ABA|C, k = 1, 那么lhs变为lhs+1，baseNum变为baseNum-1之后
                // rem = rhs-lhs‘+1 - baseNum’ = rhs-(lhs+1)+1-(baseNum-1) = rem不变，继续大于k，
                // 这会继续移动lhs直到while跳出，那时再求最长子字符串长度max(rtn, rhs-lhs+1)，一定不会超过rtn
                // 因此不影响最终结果，即使对于例子1，ABAC，k=1，中间会认为BAC是符合条件的值，这不对，但是不会影响结果
                //
                // 如果s[lhs]的值与base不同，比如：|BAA|B, k = 1, 那么lhs变为lhs+1，此时baseNum不变
                // rem = rhs-lhs‘+1 - baseNum = rhs-(lhs+1)+1-baseNum = rem-1 会变小，不会到值while死循环
            }
            rtn = max(rtn, rhs-lhs+1);// 此时窗长内都是可以通过替换k个字符达到相同的，所以直接用窗长来更新
            rhs++;// 跳出while说明满足条件，为保障下次操作，移动右边界了
        }
        return rtn;
    }
};

int main(int argc, const char * argv[]) {
    Solution gua;
    int rtn, k;
    string s;
    rtn = gua.characterReplacement(s = "ABAC", k=1);
    cout << "expect value = 3, actual value = " << rtn << endl;

    rtn = gua.characterReplacement(s = "BAAC", k=1);
    cout << "expect value = 3, actual value = " << rtn << endl;
    return 0;
}

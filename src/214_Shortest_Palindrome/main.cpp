
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    // 因为是固定从左边加入字符，所以一个tricky的本题应该可以不用O(n^2)的复杂度就可以解决
    //Runtime: 4 ms, faster than 73.37%
    //Memory Usage: 7.9 MB, less than 43.42%
    string shortestPalindrome(string s) {
        int size = s.size();
        if (size < 2) return s;
        
        string tmp = s;
        tmp.push_back('#');// 加个不是lowercase的字符#，用于解决aaa的情况，让aaa的结果不至于变成aaaaaa
        for (int i = size-1; i >= 0; --i) tmp.push_back(s[i]);

        int len = tmp.size();
        // dp含义是前后缀长度，即以tmp[0]为开始的子串和以tmp[i]为结束的子串组成的parlindrom的长度的一半，也就是s的最长前缀长度；
        vector<int> dp(len); //初始化为0，尤其是dp[0]为0
        for (int i = 1; i < len; ++i) {
            int k = dp[i-1];// 记录前一个状态，也即是长度
            while (k > 0 && tmp[i] != tmp[k]) {
                k = dp[k-1];// 当i与(k-1)+1这个位置的char不同时，回退前缀
            }
            k += (tmp[i] == tmp[k]);// 已经回退到头了，看看有没有可能让长度增加1，因为一个char与自己必然是回文
            dp[i] = k;// 再更新当前位置的前后缀长度
        }
        // 跳出循环了，构造返回数组，在s前面增加、去除最长前缀之后剩下部分的逆序字串
        tmp = s.substr(dp[len-1]);//s.begin()+dp[len-1]
        reverse(tmp.begin(), tmp.end());
        tmp.insert(tmp.end(), s.begin(), s.end());//为何如此大意tmp.begin()
        return tmp;
    }
    
    // O(n)检查是否合适palindrome
    bool getParlindrome(string &s, int y) {
        // int size = s.size();
        int i = 0, j = y;
        while (i <= j) {
            // --x;++y;
            if (s[i] == s[j]) {
                ++i; --j;
            } else {
                return false;
            }
        }
        return true; // return {x+1, y};
    }
    
    // 时间复杂度O(n^2)，对于n规模为10^4的情况，会超时
    string shortestPalindrome1(string s) {
        int size = s.size();
        if (size < 2) return s;// 空字符和一个字符都parlindrom？
        
        // 从右往左遍历，尝试找到一个最大的
        int i = size-1;
        for (; i>= 0; --i) {
            // 现在判断[0,i]是不是回文
            // x = i/2, y = (i+1)/2;
            if (getParlindrome(s, i)) {
                // 表明此时的s[0,i]就是最长的子串，那么仅需要在s前面补上s[i+1,size)这个子数组的反序就好
                break;
            }
        }
        //string rtn(s.rbegin(), s.rend()+i+1);
        string rtn = s.substr(i+1);
        reverse(begin(rtn), end(rtn));
        //rtn.insert(rtn.end(), s.begin(), s.begin()+i+1);
        rtn.insert(rtn.end(), s.begin(), s.end());
        return rtn;
    }
};

int main(int argc, const char * argv[]) {
    Solution gua;
    string rtn, s;

    rtn = gua.shortestPalindrome(s = "abcd");
    cout << "expect value = dcbabcd, actual value = " << rtn << endl;

    rtn = gua.shortestPalindrome(s = "aacecaaa");
    cout << "expect value = aaacecaaa, actual value = " << rtn << endl;
    
    rtn = gua.shortestPalindrome(s = "aba");
    cout << "expect value = aba, actual value = " << rtn << endl;

    return 0;
}

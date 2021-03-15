
#include <iostream>
#include <unordered_map>

using namespace std;

class Solution {
public:
    //Runtime: 4 ms, faster than 80.73%
    //Memory Usage: 6.6 MB, less than 67.55%
    int longestPalindrome(string s) {
        unordered_map<char,int> dict;
        for (char c : s) dict[c]++;
        
        int rtn = 0, oddCnt = 0;
        for (auto & [key, cnt] : dict) {
            //isOdd = cnt & 0x1; 大意啦大意啦！！！
            bool isOdd = cnt & 0x1;
            oddCnt += isOdd;
            // 对于偶数的话全部加入rtn中；对于奇数仅仅添加偶数部分到rtn
            rtn += (cnt - isOdd);
        }
        //if (isOdd) rtn++;
        if (oddCnt) rtn++;
        return rtn;
    }
};

int main(int argc, const char * argv[]) {
    Solution gua;
    int rtn;
    string s;
    
    rtn = gua.longestPalindrome(s = "ccd");
    cout << "expect value = 3, actual value = " << rtn << endl;

    rtn = gua.longestPalindrome(s = "abccccdd");
    cout << "expect value = 7, actual value = " << rtn << endl;

    rtn = gua.longestPalindrome(s = "a");
    cout << "expect value = 1, actual value = " << rtn << endl;
    
    rtn = gua.longestPalindrome(s = "bb");
    cout << "expect value = 2, actual value = " << rtn << endl;
    return 0;
}

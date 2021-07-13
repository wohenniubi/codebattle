
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    //Runtime: 4 ms, faster than 33.73%
    //Memory Usage: 6.5 MB, less than 50.30%
    string makeLargestSpecial(string s) {
        if (s.empty()) return "";
        
        // 非常巧妙的办法，special binary string本质上就是左右括号，也相当于间隔interval
        // 那么找到最大的那个string相当于就是把多个合法的括号pair进行排序，最长的放在前面；那么现在就是找到合法的括号pair
        vector<string> pairs;
        string rtn;

        int cnt = 0, i = 0;// 用于统计左括号和右括号，当i为0时，说明是合法的括号pair，其实等价于一个栈
        for (int j = 0; j < s.size(); ++j) {
            cnt += (s[j] == '1')?1:-1;
            if (cnt == 0) {
                // 等于0的时候说明，i到j这部分字符串是个合法的括号对
                // 此时再对去除左括号和右括号的内部子字符串进行递归调用，由此可以省略很多代码
                
                // 整个长度是j-i+1，去除前后各1个字符之后，长度只剩j-i+1 -2, 然后是从i+1开始截取
                string tmp = makeLargestSpecial(s.substr(i+1, j-i-1));
                
                // 将这个合法括号对当做一个整体，放到vector里面，后续会进行排序
                pairs.push_back("1" + tmp + "0");
                
                // 保证括号对计算正确，更新i
                i = j + 1;
            }
        }
        
        // for循环之后找到了所有的合法括号pair，此时要把长的pair放在左边，才能保证largest lexicographic
        sort(begin(pairs), end(pairs), greater<string>());// 默认是把短的字符串放在左边
        for (auto & pair: pairs)
            rtn.append(pair); //rtn.append(begin(pair), end(pair));//
        return rtn;
    }
};

int main(int argc, const char * argv[]) {
    Solution gua;
    string rtn, s;
    
    rtn = gua.makeLargestSpecial(s = "11011000");
    cout << "expect result = 11100100, actual result = " << rtn << endl;

    rtn = gua.makeLargestSpecial(s = "10");
    cout << "expect result = 10, actual result = " << rtn << endl;

    return 0;
}

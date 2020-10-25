//
//  main.cpp
//  91_Decode_Ways
//
//  Created by Jiafan Wang on 10/21/20.
//

#include <iostream>

using namespace std;

class Solution {
public:
    //Runtime: 0 ms, faster than 100.00%
    //Memory Usage: 6.3 MB, less than 5.67%
    int numDecodings(string s) {
        // 感觉还是DP问题，只不过多了一点点东西
        int len = s.size();
        if (s[0] == '0') return 0;
        for (int i = 1; i < len; ++i) {
            // 如果当前位置是0，前一位也为0或者前一位不是1或者2，那么无法decode
            if (s[i] == '0' && (s[i-1] > '2' || s[i-1] == '0'))
                return 0;
        }
        
        // 空间压缩
        int n1Ways = 1, nWays = 1;
        for (int i = 1; i < len; ++i) {
            // dp[i] = dp[i-1] + (s[i-1]>'2')?0:dp[i-2];
            swap(n1Ways, nWays);
            if (s[i] != '0')//当s[i]=='0'时沿用dp[n-2]，而已经进行了交换，于是dp[n-2]此刻就是nWays，即不需要改变nWays
            //nWays = n1Ways + (s[i-1]>'2' || s[i]>'6')? 0: nWays; 大意啦大意啦！！！！三目运算符?比+的优先级低
            // nWays = n1Ways + ((s[i-1]>'2' || s[i]>'6')? 0: nWays); 别漏掉了s[i-1]是0的情况啊
            //nWays = n1Ways + ((s[i-1]>'2' || s[i-1] == '0' || s[i]>'6')? 0: nWays); overkill了s[i]>'6'时，仅仅在s[i-1]>'1'时不能使用dp[i-2]组成结果
            nWays = n1Ways + ((s[i-1]>'2' || s[i-1] == '0' || (s[i]>'6' && s[i-1]>'1'))? 0: nWays);
            //cout << "n1Ways = " << n1Ways << ", nWays = " << nWays << ", s[i] = " << s[i] << endl;
        }
        // 测试一下
        // s = '0', 检测部分就返回0
        // s = '1', 返回nWays = 1
        // s = '12', 返回1+1，修改n1Ways初始化为1
        // s = ‘226’, 22返回是2，2返回1，226返回3
        // s = '27', 返回1，增加s[i]>'6'的判断
        // s = '17'，返回2，7可以与1组成结果
        // s = '10', 漏掉了这个用例，此时0不能单独decode（不能借用dp[n-1]），只能使用dp[n-2]
        // s = ‘2101’,跪在这个用例，此时最后的1不能与前面的0构成组合，即不能借用dp[n-2], 只能用dp[n-1]
        return nWays;
    }
};

int main(int argc, const char * argv[]) {
    Solution gua;
    int rtn;
    string s;

    rtn = gua.numDecodings(s = "2611055971756562"); //"2611055971756562"
    cout << "expect value = 4; actual value = " << rtn << endl;

    rtn = gua.numDecodings(s = "2101");
    cout << "expect value = 1; actual value = " << rtn << endl;

    rtn = gua.numDecodings(s = "210");
    cout << "expect value = 1; actual value = " << rtn << endl;

    rtn = gua.numDecodings(s = "12");
    cout << "expect value = 2; actual value = " << rtn << endl;
    return 0;
}

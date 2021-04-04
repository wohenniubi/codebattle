
#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    //Runtime: 0 ms, faster than 100.00%
    //Memory Usage: 6 MB, less than 19.83%
    int nextGreaterElement(int n) {
        // 一个32bit的int，正数取值范围[1,2147483647]
        // 因此数字总共有10位，然后对其进行排列组合，暂不考虑重复，可能有10!这么多种
        // 暴力不行的话，就要考虑特性，最后才是剪枝+memo
        // 例子1：n=12，对于数组{1,2}，其中1右侧的第一个大于1的数是2，存在；然后再把剩下的数字递增排列
        vector<int> digits;
        int num = n;
        while (num) {
            digits.push_back(num%10); // digits是倒序的，例如n=12,digits=[2,1]
            num /= 10;
        }
        reverse(digits.begin(), digits.end());//[1,2] 不需要reverse
        
        vector<pair<int,int>> st;
        for (int i = 0; i < digits.size(); ++i) {
            pair<int,int> tmp = {i, -1};
            for (int j=i+1; j < digits.size(); ++j) {
                if (digits[i] >= digits[j]) continue;
                
                if (tmp.second == -1) {
                    tmp.second = j;
                } else {
                    if (digits[tmp.second] > digits[j])
                        tmp.second = j; // 总是记录超过i的最小的j
                }
            }
            if (tmp.second != -1) {
                st.push_back(tmp);
                //break; 不能跳出，要找到最后的一组
            }
        }
        int rtn = -1;
        if (st.size()) {
            swap(digits[st.back().first], digits[st.back().second]);
            sort(digits.begin()+st.back().first+1, digits.end());

            rtn = 0;
            for (int j = 0; j < digits.size(); ++j) {
                // 防火防盗防溢出啊
                if (rtn > 214748364 || (rtn == 214748364 && digits[j] > 7)) {
                    rtn = -1;
                    break;
                }
                rtn = rtn*10 + (digits[j]);
            }
        }
        return rtn;
    }
};


int main(int argc, const char * argv[]) {
    // insert code here...
    Solution gua;
    int rtn, n;
    rtn = gua.nextGreaterElement(n = 2147483486);
    cout << "expect value = -1, actual value = " << rtn << endl;
    
    rtn = gua.nextGreaterElement(n = 12);
    cout << "expect value = 21, actual value = " << rtn << endl;
    
    rtn = gua.nextGreaterElement(n = 21);
    cout << "expect value = -1, actual value = " << rtn << endl;
    
    rtn = gua.nextGreaterElement(n = 1234);
    cout << "expect value = 1243, actual value = " << rtn << endl;

    rtn = gua.nextGreaterElement(n = 1254);
    cout << "expect value = 1425, actual value = " << rtn << endl;
    
    return 0;
}





#include <iostream>

using namespace std;

class Solution {
public:
    // 1            1                           [1,9]
    // 11     10,11,12,13,14,15,16,17,18,19     [10,19]
    // 1            21                          [20,29]
    // 1            31                          [30,39]
    // 1            41                          [40,49]
    // 1            51                          [50,59]
    // 1            61                          [60,69]
    // 1            71                          [70,79]
    // 1            81                          [80,89]
    // 1            91                          [90,99]
    // 11      100,101,102,103,104,105,106,107,108,109   [100,109]
    // 21      110,111,112,113,114,115,116,117,118,119   [110,119]
    // 11      120,121,122,123,124,125,126,127,128,129   [120,129]
    // ..
    // 1            201                         [200,209]
    //Runtime: 0 ms, faster than 100.00%
    //Memory Usage: 5.8 MB, less than 79.55%
    int countDigitOne(int n) {
        int rtn = 0, org = n, pk = 0;
        
        // 还是采用这种思路通用一些，每次以y这个位置分割原本的数据，在y这个位置取1，253[y]23
        // 那么包含了1的数字的个数会大致等于y左侧的数字个数 * y右侧的组合个数，然后再向左移动y
        while (n) {
            int y = n%10;
            n /= 10;//n变成y左侧的数字
            pk *= 10;
            if (!pk) pk = 1;
                
            // y的值会影响包含1的数据组成，因为题目要求不大于n
            if (0 == y) {
                // org也从y拆成两半，y左侧部分只能取0~n-1（y左侧不能取n，否则y=1就会大于原始数据）y右侧任意
                rtn += (n*pk);
            } else {
                if (1 == y) {
                    // 分成两部分，y左侧是0~n-1, y左侧是n；后者的话要取原始数据对power(10,k)的模
                    // rtn += (n*power(10,k) + org%power(10,k));
                    rtn += (n*pk + org%pk + 1);//取模之后还要加1位，00嘛
                } else {
                    ;// 大于1，那么可以任意组合，杀疯了
                    // rtn += ((n+1)*power(10,k));
                    rtn += ((n+1)*pk);
                }
            }
            //++k;// k表示level，即y右侧的digit位
        }
        return rtn;
    }
};

int main(int argc, const char * argv[]) {
    Solution gua;
    int rtn, n;
    rtn = gua.countDigitOne(n = 13);
    cout << "expect value = 6, actual value = " << rtn << endl;
    
    rtn = gua.countDigitOne(n = 0);
    cout << "expect value = 0, actual value = " << rtn << endl;

    rtn = gua.countDigitOne(n = 100);
    cout << "expect value = 21, actual value = " << rtn << endl;

    return 0;
}

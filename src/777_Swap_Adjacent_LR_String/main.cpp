
#include <iostream>

using namespace std;

class Solution {
public:
    //Runtime: 4 ms, faster than 98.20%
    //Memory Usage: 7.5 MB, less than 71.65%
    //一道智力题，理解了题意之后，R只能借助X右移，L只能借助X左移，且R和L不能相互跨越，所以本质就是括号问题
    //start中的R是[左括号，end中的R是右括号]，end中的L是{左括号，start中的L是}右括号，使用加减操作可以完美解决
    bool canTransform(string start, string end) {
        if (start.size() != end.size()) return false;
        int n = start.size();
        
        int cntR = 0, cntL = 0;
        for (int i = 0; i < n; ++i) {
            if (start[i] == 'R') {
                if (cntL > 0) return false;
                ++cntR;
            }
            if (end[i] == 'R') {
                if (cntR == 0) return false;
                --cntR;
            }
            if (end[i] == 'L') {
                if (cntR > 0) return false;
                ++cntL;
            }
            if (start[i] == 'L') {
                if (cntL == 0) return false;
                --cntL;
            }
        }
        // return true;
        return cntR == 0 && cntL == 0;
    }
};

int main(int argc, const char * argv[]) {
    Solution gua;
    string s, t;
    bool rtn;
    
    rtn = gua.canTransform(s = "X", t = "L");
    cout << "expect value = 0, actual value = " << rtn << endl;

    rtn = gua.canTransform(s = "XL", t = "LX");
    cout << "expect value = 1, actual value = " << rtn << endl;

    rtn = gua.canTransform(s = "XLLR", t = "LXLX");
    cout << "expect value = 0, actual value = " << rtn << endl;

    rtn = gua.canTransform(s = "RXXLRXRXL", t = "XRLXXRRLX");
    cout << "expect value = 1, actual value = " << rtn << endl;

    rtn = gua.canTransform(s = "LLR", t = "RRL");
    cout << "expect value = 0, actual value = " << rtn << endl;
    return 0;
}

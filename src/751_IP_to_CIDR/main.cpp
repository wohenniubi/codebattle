
#include <iostream>
#include <sstream>
#include <vector>
#include <cmath>

using namespace std;

class Solution {
public:
    //Runtime: 0 ms, faster than 100.00%
    //Memory Usage: 6.7 MB, less than 63.79%
    vector<string> ipToCIDR(string ip, int n) {
        // 两个巧妙的地方，第一个是把IP地址转化为一个long整型数x，然后再利用x&-x的技巧得到最低位的1
        // 再计算这个1后面的所有bit位可以代表的IP个数step
        // 1）如果个数不超过n，那么这些数都可以由x + log2(step)掩码覆盖
        // 2）如果个数超过n，那么就把step折半直到小于等于n，再由x + log2(step)掩码覆盖
        // 之后更新n和x，继续loop执行
        vector<string> rtn;
        istringstream is(ip);
        string t;
        long x = 0;
        while (getline(is, t, '.')) {
            x = x*256 + stoi(t);// 每次以256（8个比特）作为分割，很巧妙
        }
        
        // 针对全零的corner case，实在想不出好办法，专门写个分支来处理吧
        if (!x) {
            vector<int> steps;
            while (n) {
                int step = n & -n;
                steps.push_back(step);
                n -= step;
            }
            while (steps.size()) {
                rtn.push_back(long2CIDR(x, steps.back()));
                x += steps.back();
                steps.pop_back();
            }
        } else {
            while (n) {
                long step = x & -x;

                while (step > n) {
                    step >>= 1;
                }//n必然>=1，因此跳出while的step不可能为0

                // x + 得到的step就可以组成所需的CIDR
                // rtn = long2CIDR(x, step);
                rtn.push_back(long2CIDR(x, step));

                // 保证while循环，更新x和n
                x += step;
                n -= step;
            }
        }
            
        return rtn;
    }
    
    string long2CIDR(long x, long step) {
        int n = 0;
        while (step) {
            step >>= 1;
            ++n;
        }
        n = 33 - n;
        string rtn = to_string(x >> 24) + "." + to_string((x >> 16) & 255) + ".";
        rtn += to_string((x >> 8) & 255) + "." + to_string(x & 255) + "/" + to_string(n);
        return rtn;
    }
};

ostream & operator<< (ostream &os, vector<string> &rtn) {
    os << "[";
    for (auto & ip : rtn) {
        os << ip << ", ";
    }
    
    os << "]";
    return os;
}

int main(int argc, const char * argv[]) {
    Solution gua;
    vector<string> rtn;
    string ip;
    int n;
    
    rtn = gua.ipToCIDR(ip = "0.0.0.0", n = 2);
    cout << rtn << endl;

    rtn = gua.ipToCIDR(ip = "0.0.0.0", n = 1);
    cout << rtn << endl;

    rtn = gua.ipToCIDR(ip = "127.0.0.12", n = 4);
    cout << rtn << endl;

    rtn = gua.ipToCIDR(ip = "255.0.0.7", n = 10);
    cout << rtn << endl;
    return 0;
}

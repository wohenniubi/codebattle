#include <iostream>

using namespace std;

class Solution {
public:
    #define MAXM 1000000007
    
    int countOrders(int n) {
        // 不用想，这种“模棱两可”的要求，肯定是dp操作，那么问题来了，如何设置子问题
        // 可以首选基于递归的dp操作， 然后竟然推导出了子问题，哇咔咔咔，我很牛逼
        
        // dp[1] = 1;
        // dp[2] = 6;
        // dp[3] = 90; 这90个是这样组成的
        // | | | | 代表dp[2]的一个pattern；为了让新增的P3D3保证顺序，那么
        // P3D3作为一个整体往| | | |里面放，或者说中间隔0个|，总共有5种方式(||||的长度+1)
        // P3D3中间隔1个|，总共有4种方式
        // P3D3中间隔2个|，总共有3种方式
        // P3D3中间隔3个|，总共有2种方式
        // P3D3中间隔4个|，总共有1种方式
        // 加起来有1+2+...+5共15种方式，乘以dp[2]=6，就等于dp[3]=90，于是整理一下，看下面代码
        
        int rtn = 1;// 代表n=1
        // if-0的分支写出了基本原理，但是绝对会overflow。所以另想办法
        if (1) {
            long prev = rtn;
            for (int i = 2; i <= n; ++i) {
                int cnt = 2*(i-1) + 1;// 整体个数，然后是首项加末项的操作
                int num = (1+cnt)*cnt/2;//n不会超过500，cnt不会超过1000，num不会超过1000000
                prev = ((prev % MAXM) * num) % MAXM;
            }
            rtn = prev;
        } else {
            for (int i = 2; i <= n; ++i) {
                long prev = 0;
                
                for (int j = 1; j < 2*i+1; ++j) {
                    prev += ((long)rtn*j);
                    prev %= MAXM;
                }
                
                rtn = prev;
            }
        }
        
        return rtn;
    }
};

int main(int argc, const char * argv[]) {
    Solution gua;
    int rtn, n;
    
    rtn = gua.countOrders(n=1);
    std::cout << "expect value = 1, actual value = " << rtn << endl;
    
    rtn = gua.countOrders(n=2);
    std::cout << "expect value = 6, actual value = " << rtn << endl;
    
    rtn = gua.countOrders(n=3);
    std::cout << "expect value = 90, actual value = " << rtn << endl;
    
    return 0;
}


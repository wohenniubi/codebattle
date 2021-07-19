
#include <iostream>

using namespace std;

class Solution {
public:
    // 第三种牛顿法，切线法的泰勒级数逼近
    // Runtime: 4 ms, faster than 14.84%
    // Memory Usage: 6 MB, less than 14.81%
    bool isPerfectSquare(int num) {
        // 这里相当于一个函数y，它等于x^2 - num，然后要计算y = 0时候的x
        // 于是泰勒级数逼近就是x_(n+1) = x_(n) - f(x(n))/f'(x(n))
        // int x = num; 大意了，对于较大的num值，会导致int越界
        if (num < 0) return false;//有这一行安全一些，比如传入num = 1367890*1367890，此时num为负数，下面的while会死循环
        long x = num;
        
        while (x * x > num) {
            x = (x + num/x)/2;// y对x求导数的到2x，代入得到x - (x^2 - num)/2x，然后化简的到 x/2 + num/2x
        }// 由于x不断减小，所以循环条件就是要保证x^2要大于num
        
        return (x*x == num);// 跳出循环后再补一个判断，处理完成
    }
    
    // 方法1：二分法
    // Runtime: 0 ms, faster than 100.00%
    // Memory Usage: 5.9 MB, less than 61.76%
    bool isPerfectSquare2(int num) {
        int lhs = 1, rhs = num;
        
        // 这里选用<=是因为rhs选择的是num，当num为1时，要等于才行
        while (lhs <= rhs) {
            long mid = (rhs - lhs)/2 + lhs;// mid的平方会出现越界的情况，所以这里用long

            if (mid*mid == num) {
                return true;
            } else if (mid*mid > num) {
                rhs = mid-1;// 要减少一位
            } else {
                lhs = mid+1;
            }
        }
        return false;
    }
    
    // Runtime: 0 ms, faster than 100.00%
    // Memory Usage: 5.9 MB, less than 61.76%
    // 方法2: x^x > num
    bool isPerfectSquare1(int num) {
        for (int i = 1; i <= num/i; ++i) {
            if (i*i == num)
                return true;
        }
        return false;
    }
};

int main(int argc, const char * argv[]) {
    Solution gua;
    bool rtn;
    int num;
    
    rtn = gua.isPerfectSquare(num = 16);
    cout << "expect value = 1, actual value = " << rtn << endl;

    rtn = gua.isPerfectSquare(num = 14);
    cout << "expect value = 0, actual value = " << rtn << endl;
    
    rtn = gua.isPerfectSquare(num = 13678*13678);
    cout << "expect value = 1, actual value = " << rtn << endl;
    return 0;
}

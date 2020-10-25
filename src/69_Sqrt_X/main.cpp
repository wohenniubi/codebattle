
#include <iostream>

using namespace std;

class Solution {
public:
    //Runtime: 0 ms, faster than 100.00%
    //Memory Usage: 6.4 MB, less than 100.00%
    int mySqrt1(int x) {
        int lhs = 0, rhs = x;
        if (x < 0) return -1;
        
        // 找到小于等于rhs的某个index，使得其平方不大于x
        while (lhs <= rhs) {
            long long mid = lhs + (rhs - lhs)/2;
            // 此时mid就对应integer这个array里的值
            long long mid2 = mid*mid;
            
            if (mid2 == x) {
                return mid;
            } else if (mid2 > x) {
                rhs = mid-1;
            } else {
                lhs = mid+1;
            }
        }
        // 测试一下啊
        // x = 0, rtn = 0
        // x = 1, rtn = 1
        // x = 2, mid = 1, 1*1 < x, lhs = 2;
        //        mid = 2, 2*2 > x, rhs = 1;
        //        break; rtn = lhs-1 = 1
        // x = 4, mid = 2, 2*2 = x, rtn = 2;
        // x = 8, mid = 4, 4*4 > x, rhs = 3;
        //        mid = 1, 1*1 < x, lhs = 2;
        //        mid = 2, 2*2 < x, lhs = 3;
        //        mid = 3, 3*3 > x, rhs = 2;
        //        break; rtn = lhs-1 = 2
        //long long mid2 = lhs*lhs; // leetcode会报错int*int overflow
        // C++不是按照=左边的long long来对右边的操作数进行转换，而是对于运算中的两个数按照较大的类型进行转换
        // 因此只需要让*左边的lhs转换为long long，则会自动的让右边的数转换为long long
        long long mid2 = (long long)lhs*lhs;
        // return (mid2 == x)? lhs:lhs-1;
        return (mid2 > x)? lhs-1:lhs;
    }
    
    int mySqrt(int x) {
        int rtn = x;
        if (x < 2) return rtn;
        
        int lhs = 1, rhs = x/2;//对于>=2的x，折半都可以cover其sqrt；这样可以避免做乘法导致的int overflow
        while (lhs <= rhs) {
            int mid = lhs + (rhs - lhs)/2;
            if (mid <= x/mid) {
                lhs = mid+1;
                rtn = mid;
            } else {
                //mid*mid > x;
                //rhs = mid;// 大意了，x=8这里出现死循环
                rhs = mid-1;
                //此时不需要更新rtn
            }
        }
        return rtn;
    }
};

int main(int argc, const char * argv[]) {
    Solution gua;
    int rtn, x;
    
    rtn = gua.mySqrt(x=0);
    cout << "expect value = 0, actual value = " << rtn << endl;
    
    rtn = gua.mySqrt(x=4);
    cout << "expect value = 2, actual value = " << rtn << endl;
    
    rtn = gua.mySqrt(x=8);
    cout << "expect value = 2, actual value = " << rtn << endl;

    return 0;
}

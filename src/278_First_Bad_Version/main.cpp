
#include <iostream>

using namespace std;

class Solution {
    int badVersion;
public:
    void setBadVersion(int n) {
        badVersion = n;
    }
    bool isBadVersion(int n) {
        return badVersion <= n;
    }
    
    //Runtime: 0 ms, faster than 100.00%
    //Memory Usage: 6.5 MB, less than 99.98%
    int firstBadVersion(int n) {
        //典型的二分查找,1...n满足了顺序数组的条件，然后要找最早的n
        int lhs = 1, rhs = n;
        while (lhs < rhs) {
            int mid = lhs + (rhs-lhs)/2;
            if (!isBadVersion(mid)) {
                lhs = mid+1;// mid位置没有错表明前面都不会有错
            } else {
                rhs = mid;
            }
        }
        //return rhs;
        return lhs;
        // 测试一下
        // n=5, bad=4; lhs=1, rhs=5; mid=3, isBad(3)==0, lhs=4; mid=4, isBad(4)==1, rhs=4; break, return 4
        // n=2, bad=1; lhs=1, rhs=2; mid=1, isBad(1)==1, rhs=1; break, return 1;
        // n=2, bad=2; lhs=1, rhs=2; mid=1, isBad(1)==0, lhs=2; break, return 2;
    }
    
    // 使用<=也是可以的哟，我之前写的
    int firstBadVersion1(int n) {
        // my main idea is Binary search, # to invoke the API is log(n)
        int lhs = 1;
        int rhs = n;
        int erl = n;
        while (lhs <= rhs) {
            int mid = lhs + (rhs-lhs)/2;
            if (isBadVersion(mid)) {
                erl = min(erl, mid);
                rhs = mid-1;
                //rhs = mid;
            } else {
                lhs = mid+1;
            }
        }
        return lhs;
    }
};

int main(int argc, const char * argv[]) {
    Solution gua;
    int rtn, n, bad;

    gua.setBadVersion(bad=4);
    rtn = gua.firstBadVersion(n=5);
    cout << "expect value = 4, actual value = " << rtn << endl;

    gua.setBadVersion(bad=1);
    rtn = gua.firstBadVersion(n=1);
    cout << "expect value = 1, actual value = " << rtn << endl;
    return 0;
}



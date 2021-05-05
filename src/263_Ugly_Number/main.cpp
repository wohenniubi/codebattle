
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    //Runtime: 0 ms, faster than 100.00%
    //Memory Usage: 5.9 MB, less than 12.78%
    bool isUgly(int n) {
        // 非常巧的问题转化，符合条件的n必定满足n=(2^i)*(3^j)*(5^k)
        // 因此可以把n视作一个根节点，然后每次对3个可能的分支进行查询
        // 时间复杂度等于O(log2(n) + log3(n) + log5(n))，也不过是C*O(logn)
        vector<int> primes{2,3,5};
        int tmp = n;
        for (int prime : primes) {
            while (tmp) {
                if (1 == tmp)
                    return true;
                if (tmp % prime)
                    // 不应该太着急返false，还要看看下一个prime
                    break;
                tmp /= prime;
            }
        }
        
        // 跳出for循环时说明尝试过所有的prime都没有返回true，那么返回false
        return false;//例如7或11
    }
};

int main(int argc, const char * argv[]) {
    Solution gua;
    bool rtn;
    int n;
    rtn = gua.isUgly(n = 11);
    cout << "expect value = 0, actual value = " << rtn << endl;

    rtn = gua.isUgly(n = 1);
    cout << "expect value = 1, actual value = " << rtn << endl;

    return 0;
}

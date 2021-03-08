
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    #define BASE 1337
    // 用于计算(a^b)%1337
    int myPow(int a, int b) {
        if (b == 0) return 1;
        
        // 此时递归最多递归10次; 来干吧
        // a^b%k = ((a%k)^b)% k = ((a%k)%k * (a%k)^(b-1)%k) %k
        a %= BASE;
        int rtn = 1;
        for (int i = 0; i < b; ++i) {
            rtn *= a;
            rtn %= BASE;
        }
        return rtn;
    }
    //Runtime: 12 ms, faster than 80.38%
    //Memory Usage: 11.7 MB, less than 77.69%
    int superPow(int a, vector<int>& b) {
        // 要利用一个公式才能解决问题，(ab)%k = ((a%k)(b*k))%k
        // 证明：a=Ak+C b=Bk+D，其中ABCD都是正数
        // ab = ABk^2 + (AD+BC)k + CD, 所以(ab)%k = (CD)%k
        // 而从a=Ak+C b=Bk+D可以得到a%k = C, b%k = D
        // 所以代入可以得到关系式(ab)%k=(CD)%k=((a%k)(b%k))%k
                
        // 而对于幂，不过就是多个相同的数相乘
        // (a^b[i,j,k])%1337 = ((a%1337)*(a%1337)...(a%1337)) % 1337
        // = ((a%1337)%1337 * ((a%1337)^b[i,j,k-1])%1337) % 1337
        // 然后模两次算作一次(a%1337)%1337 = a%1337，所以再等价于
        // = (a%1337 * (a%1337 * ((a%1337)^b[i,j,k-2])%1337) %1337) % 1337
        // 把(a%1337)^b[i,j,k-2])%1337)看作一个整体，这就是个递归嵌套
        
        // 但是如果直接递归，那么复杂度是是b可以表示的数，即O(10^len(b))，妥妥超时
        // 所以还需要再转化一下，需要识别出子问题，然后使用递归解决
        // a^b[1,3,5] = a^5 * (a^b[1,3,0]) = a^5 * ((a^b[1,3]) ^ 10)
        // 有点像是左右分支子树的感觉
        if (b.empty())
            return 1;// (a^0)%1337 = 1

        int lsb = b.back();//lsb因此只可能是个0~9的数
        b.pop_back();
        // (a^lsb * (a^b)^10) % 1337 = ((a^lsb % 1337) * ((a^b)^10)%1337) %1337
        int lhs = myPow(a, lsb);
        int rhs = myPow(superPow(a, b), 10);
        return (lhs * rhs) % BASE;
    }
};

int main(int argc, const char * argv[]) {
    Solution gua;
    int rtn, a;
    vector<int> b;
    rtn = gua.superPow(a = 2, b = {3});
    cout << "expect result = 8, actual result = " << rtn << endl;

    rtn = gua.superPow(a = 2147483647, b = {2,0,0});
    cout << "expect result = 1198, actual result = " << rtn << endl;
    return 0;
}

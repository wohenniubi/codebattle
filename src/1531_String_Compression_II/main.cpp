
#include <iostream>

using namespace std;

//int memo[101][101][26][101];
int memo[101][101][27][101];
class Solution {
    // int memo[101][101][26][101]; 原来在class里面的array是分配在stack上面的哟，这么大的数组会导致溢出
    public:
    // 采用DP完成，最困难的是定义这里的状态dp，是四维的数组哟
    // dp(i,k,p,l) 表示一个最短的长度，对应从index i到最右端这个数组，可以删除k个char
    // 以及index i左边最近这个char对应的编号，和这个char的个数-- 这定义是不是牛逼得飞起；
    // 所有dp数据存处于memo数组，也同时作为visit数组
    // Runtime: 1012 ms, faster than 9.25%
    // Memory Usage: 115.1 MB, less than 7.49%
    int getLengthOfOptimalCompression1(string s, int k) {
        // 初始化memo数组，不使用local变量的原因是函数栈会overflow
        // 初始化为-1是因为memo需要与visit数组合并，0会作为有效的结果，所以初始化为-1
        // memset((void*)memo, 101*101*26*101*size_of(int), -1); 好久没用sizeof，大意啦
        // memset((void*)memo, -1, 101*101*26*101*sizeof(int));
        memset((void*)memo, -1, sizeof(memo));
        
        // top level调用时传入什么样的参数呢，反正小写字母-'a'之后映射为int，取值为[0,26]
        // 因此随便取一个[0,26]范围之外的数就好了
        //return dpMinLen(s, 0, k, -1, 0); 大意了，如果初始化p=-1，memo[i][k][p][l]时会越界，所以才多增加一个字符26
        return dpMinLen(s, 0, k, 26, 0);// 如果使用26的话，memo的size会从25改变为26，例如[101][101][26][101]
    }

    int dpMinLen(string &s, int i, int k, int p, int l) {
        // 返回条件：
        if (k < 0) return INT_MAX/2;// 返回一个足够大的数，担心在上一层+1溢出，所以折半
        // 2，如果剩余的char小于等于k，那么直接删完可以得到最小的长度
        if (i + k >= s.size()) return 0;
        
        // 对于k <= 0的处理，本题非常巧妙的转换为两个部分，k < 0和k==0
        // k <0认为没有最小长度，于是返回一个很大的值，这样可以进入上一层的else分支
        // k==0认为属于合法的条件，继续进入本次的if-else判断
        // if (k <= 0) {
        //     // 此时需不需要考虑前面的p和l呢？？
        //     // 计算i到s.size()这部分的run-length coding
        //     int carry = (l == 1 || l == 9 || l == 99);
        //     minLen = carry + dp();
        //     return minLen;
        // }

        // 查找memo，出于对k的合法性判断，应该放在k<0判断之后
        int &minLen = memo[i][k][p][l];
        if (minLen != -1) return minLen;
        
        if (s[i]-'a' == p) {
            // s[i]与左边的字符相同;
            // 分为两种情况，删除这个字符s[i]或者保留
            int carry = (l == 1 || l == 9 || l == 99);
            minLen = min(dpMinLen(s, i+1, k-1, p, l),
                        carry + dpMinLen(s, i+1, k, p, l+1));
            // 保留这个char的处理，需要append到左边的字符里面，可能会出现进位，那就会多贡献1位
            // 由于总长度不超过100，所以只有3种情况下会出现进位
        } else {
            // s[i]与左边的字符不同;
            // 分为两种情况，删除这个字符s[i]或者保留
            minLen = min(dpMinLen(s, i+1, k-1, p, l),
                        1 + dpMinLen(s, i+1, k, s[i]-'a', 1)); // 别大意少些个参数
            // 这里保留这个char的处理很巧妙，这里硬生生先加个1，把进位的操作留到s[i+1]这个char的s[i]-'a' == p分支来处理
            // 这样的划分非常合理，花花酱，高，实在是高
        }
        return minLen;
    }
    
    // 网上采用函数式编程实现的上述代码
    //Runtime: 1144 ms, faster than 8.41%
    //Memory Usage: 115.4 MB, less than 5.31%
    int getLengthOfOptimalCompression(string s, int k) {
        memset(memo, -1, sizeof(memo));
        
        // 前面这个[&]表明要把外部变量以&的方式，作为函数可见的变量，全局变量属于外部变量
        function<int(int,int,int,int)> dp = [&](int i, int k, int last, int len) -> int{
            // 返回条件，暂时空着吧
            // 肯定要判断k<0，别大意忘记了
            if (k < 0) return INT_MAX/2;
            if (i + k >= s.size()) return 0;
            
            int & minLen = memo[i][k][last][len];
            if (minLen != -1) return minLen;
            
            // 接下来开始计算，拆分为当前字符s[i]与上一个字符是否相同的两种情况;
            // 每种情况又分为删除和保留两种情况
            if (s[i]-'a' == last) {
                // 当前字符与上一个字符相同时也分为保留和删除两种情况，此时直接操作如下；
//                minLen = min(dp(i+1, k-1, last, len),
//                             dp(i+1, k, last, len+1));
                // 不过我经验的感觉可以去掉删除char的这种情况：因为对于run-length encode这种方式
                // 删除一个相同的字符貌似不会得到最短的长度，所以只选保留的这个情况吧
                // 大意了，要加上进位的考虑carry
                int carry = (len == 1|| len == 9 || len == 99);
                minLen = dp(i+1, k, last, len+1) + carry;
            } else {
                minLen = min(dp(i+1, k-1, last, len),
                          1 + dp(i+1, k, s[i]-'a', 1));
                // 对于字符不同且保留这个字符的情况，更新last的值，并且重置len=1，
                // 然后增加一个长度，至于是否进位，留给下一级的dp根据长度len进行判断
            }
            
            return minLen;
        };
        return dp(0, k, 26, 0);
    }
};

class Solution2 {
    int cache[101][101];//dp数组，dp(i,k)表示从i到n的这段数组允许删除k个字符时的最短长度
    public:
    // 还是采用dp来做，优化了上面的4维数组，采用“内卷”的方式，减少了空间复杂度，估计一时半会儿想不到这种做法
    // Runtime: 36 ms, faster than 95.13%
    // Memory Usage: 6.6 MB, less than 81.42%
    int getLengthOfOptimalCompression(string s, int k) {
        memset(cache, -1, sizeof(cache));
        return dp(s, 0, k);
    }
    
    int dp(string & s, int i, int k) {
        // 返回条件还没有确定，先空着，后面别忘了写
        if (k < 0) return INT_MAX/2;
        if (i + k >= s.size()) return 0;
        if (cache[i][k] != -1) return cache[i][k];
        
        //int diff = 0, same = 1, len = 1;
        int diff = 0, same = 0, len = 0;
        //int rtn = INT_MAX/2;// 因为要找最小，初始化为较大的值，一半的值足够大了
        // 这里非常巧妙的初始化，假设去掉当前的char，这样很好的应对了"abb"的这种情况
        int rtn = dp(s, i+1, k-1);
        
        // 基本思路：在内部操作时从当前位置i向右遍历，遇到不同的char就删除，这样可以最大程度的压缩相同字符
        //for (int j = i+1; j < s.size() && k-diff >= 0; ++j) { 之所以不用i+1是因为可能一次都没有运算就跳出了；
        // 或者说，如果用j=i+1，那么还要为j进行合法判断，麻烦了就容易出错
        for (int j = i; j < s.size() && k-diff >= 0; ++j) {
            // 加入了一个k-diff与0的判断是为了减少分支，之所以允许k=diff，是为了处理s="aaaa",k=0的情况
            if (s[j] == s[i]) {
                // 这里相当于进位的考虑
                //if (same == 1 || same == 9 || same == 99) len++;
                if (same <= 1 || same == 9 || same == 99) len++;
                ++same;
            } else {
                ++diff;
                // 对于不同的处理是删除这个char，并不影响len和same
            }
            // 传入剩下的可删除char个数
            rtn = min(rtn, len + dp(s, j+1, k-diff));
        }
        return cache[i][k] = rtn;
    }
};

int main(int argc, const char * argv[]) {
    Solution2 gua;
    int rtn, k;
    string s;

    rtn = gua.getLengthOfOptimalCompression(s = "abb", k = 1);
    cout << "expect value = 2, actual value = " << rtn << endl;

    rtn = gua.getLengthOfOptimalCompression(s = "aaabcccd", k = 2);
    cout << "expect value = 4, actual value = " << rtn << endl;
    return 0;
}


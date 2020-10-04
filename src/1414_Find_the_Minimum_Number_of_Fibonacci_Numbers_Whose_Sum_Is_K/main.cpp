
#include <iostream>
#include <unordered_map>
#include <vector>
#include <experimental/iterator>

using namespace std;

class Solution {
public:
    // 用于计算最少个数的fibs sum, dfs模版写法; 但是超时呀超时啊！！！
    int dfs(vector<int> &fibs, int k, unordered_map<int,int> &dict) {
        int rtn = INT_MAX;
        if (k == 0) return 0;
        if (k <= 3) return 1;// fibs = 1,1,2,3,5,8,13...
        if (dict.count(k)) return dict[k];
        
        // 因为fibs是ordered的序列，greedy的从后往前找，或可以提速
        //for (int i = size(fibs)-1; i >= 0; --i) {
        for (int i = fibs.size()-1; i >= 0; --i) {
            int tmp = fibs[i];
            if (tmp > k) continue;
            
            rtn = min(rtn, 1 + dfs(fibs, k-tmp, dict)); //大意了大意了，忘记加1
        }
        return dict[k] = rtn;
    }
    
    int findMinFibonacciNumbers1(int k) {
        vector<int> fibs;// fibs{1}
        int f1 = 1, f2 = 1;
        // 首先获得小于等于k得fibs序列，便于后面进行处理
        for (; f2 <= k; ) {
            fibs.push_back(f2);
            f2 += f1;// f2' = f1+f2
            f1 = fibs.back(); //f1' = f2;
        }
        
        unordered_map<int,int> dict;
        return dfs(fibs, k, dict);
    }
    
    //Runtime: 0 ms, faster than 100.00%
    //Memory Usage: 6.6 MB, less than 24.02%
    //Runtime: 4 ms, faster than 75.98%
    //Memory Usage: 6.5 MB, less than 47.95%
    //时间复杂度O(logk * logk)：因为Fibonacci数列成倍数增大，类似于2^x次方，所以数列长为logk；然后要循环logk次
    //空间复杂度还可以优化为O(1)：此时不再使用vector来存，改用相邻的两个值就可以计算出来下一个和前一个
    int findMinFibonacciNumbers(int k) {
        vector<int> fibs;// fibs{1}
        int f1 = 1, f2 = 1;
        // 首先获得小于等于k得fibs序列，便于后面进行处理
        for (; f2 <= k; ) {
            fibs.push_back(f2);
            f2 += f1;// f2' = f1+f2
            f1 = fibs.back(); //f1' = f2;
        }
        
        int rtn = 0, r = fibs.size()-1;
        while (k != 0) {
            // 可以进一步优化，例如：给这个fibs一个右边界，当右边界的值大于k时，就缩短fibs
            // 这样可以避免每次都要loop fibs数组；不过修改之后貌似leetcode的runtime没啥改进
            for (int i = r; i>= 0; --i) {
                if (fibs[i] > k) {
                    r--;
                    continue;
                }
                // 为什么可以这样，不怕减掉fibs[i]之后凑不到k吗？
                // 先记下来吧，可能Fibonacci数列有其特别的性质，暂时不明
                k-= fibs[i];
                rtn++;
            }
        }
        return rtn;
    }
};

int main(int argc, const char * argv[]) {
    Solution gua;
    int rtn, k;
    rtn = gua.findMinFibonacciNumbers(k = 374602);
    cout << "expect value = 9, actual value = " << rtn << endl;

    rtn = gua.findMinFibonacciNumbers(k = 7);
    cout << "expect value = 2, actual value = " << rtn << endl;
    
    return 0;
}

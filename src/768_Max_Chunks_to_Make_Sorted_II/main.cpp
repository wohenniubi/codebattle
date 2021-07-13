
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    //Runtime: 12 ms, faster than 58.22%
    //Memory Usage: 12.4 MB, less than 60.00%
    int maxChunksToSorted(vector<int>& arr) {
        //int rtn = 0;
        int rtn = 1;// 为了应对一个块的情况，初始化为1
        int n = arr.size();
        
        // 使用两个数组forward和backward，其中前者表示[0,i]范围内的最大数字，后者表示[i,n-1]中的最小数字
        // 可以分块的前提是，i之后的数字不比当前块中的任何数字小，也即是说i之后最小的数字不能比目前最大的数字小，
        // 否则这个分块要继续延伸，这样才能保证独立排序之后，较小的数字可以排在较大数字左边
        vector<int> f = arr, b = arr;
        for (int i = 1; i < n; ++i)
            f[i] = max(f[i-1], f[i]);
        
        for (int i = n-2; i >= 0; --i)
            b[i] = min(b[i+1], b[i]);

        // 然后借助f和b，开始扫描判断
        for (int i = 0; i < n-1; ++i) {
            if (f[i] <= b[i+1]) // 注意要与下一个值i+1相比，如果是f[i]<=b[i]，那么每个值与自身相比都满足这个条件
                ++rtn;//题目是最大可以划分的块，所以直接+1
        }
        
        return rtn;//如果上述for loop不执行，rtn至少为1
    }
    
    // 看了答案，这么屌的操作，怎么想到的；那道arr里面是[0,n-1]的不重复数的方法不行了
    int maxChunksToSorted1(vector<int>& arr) {
        int rtn = 0;
        vector<int> afsort = arr;
        sort(begin(afsort), end(afsort));
        
        // int sum1, sum2 = 0;// 大意了，int搞不定啊
        // long sum1, sum2 = 0; // 这样写的话，有些编译器会认为sum1没有初始化
        long sum1 = 0, sum2 = 0;
        for (int i = 0; i < arr.size(); ++i) {
            sum1 += arr[i];
            sum2 += afsort[i];
            
            if (sum1 == sum2) {
                ++rtn;
            }
        }
        
        return rtn;
    }
};

int main(int argc, const char * argv[]) {
    Solution gua;
    vector<int> arr;
    
    int rtn;
    rtn = gua.maxChunksToSorted(arr = {2,1,3,4,4});
    cout << "expect value = 4, actual value = " << rtn << endl;

    rtn = gua.maxChunksToSorted(arr = {5,3,3,2,1});
    cout << "expect value = 1, actual value = " << rtn << endl;
    return 0;
}


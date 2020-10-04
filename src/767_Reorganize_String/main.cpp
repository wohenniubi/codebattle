#include <iostream>
#include <unordered_map>
#include <queue>
#include <vector>

using namespace std;

// Greed做法不OK，对于baaba就跪了
class Solution1 {
public:
    string reorganizeString(string S) {
        int size = S.size();
        if (size < 2) return S;// ""和单个字符都是返回其本身
        
        string tmp = S;
        for (int i = 1; i < size; ++i) {
            int j = size-1;
            while (tmp[i] == tmp[i-1]) {
                if (i < j) {
                    swap(tmp[i], tmp[j]);
                    j--;
                } else {
                    return "";// 当前i没有办法替换找到与i-1不同的char
                }
            }
        }
        
        return tmp;
    }
};

//Runtime: 4 ms, faster than 78.09%
//Memory Usage: 6.3 MB, less than 77.95%
struct myCmp {
    bool operator()(const pair<int,char> &A, const pair<int, char> &B) {
        return A.first < B.first;// 大堆
    }
};

class Solution {
public:
    // 把char和其出现次数进行匹配，非常巧妙
    string reorganizeString(string S) {
        string res = "";
        unordered_map<char, int> dict;
        //priority_queue<pair<int, char>> helper;//也可不定myCmp，默认的build-in比较函数可搞定pair<int,char>
        priority_queue<pair<int, char>, vector<pair<int, char>>, myCmp> helper;
        
        int size = S.size();
        for (char s : S) dict[s]++;
        // 将所有的char以及出现次数入heap
        for (auto [key, cnt] : dict) {
            if (cnt > (size+1)/2) return "";
            // 含义是如果某个char出现的次数大于总长度的一半，那么必定不能reorganize
            // 证明：假设某个char出现次数为m，总长为n，若大于总长的一半即m > (n+1)/2
            // 这里+1的原因是解决奇偶数除法的问题，baaba的m=3，n=5，是有解的；baba的m=2,n=4是有解的
            // 而为了保证这m个char不彼此相连，至少需要m-1个其他字符；而其他字符只有n-m个；
            // 将两个数进行相减(n-m)-(m-1) = n-2m+1，而有m>(n+1)/2，即2m>n+1 => n-2m + 1 < 0
            // 说明剩余的其他字符尚且不够让出现次数为m的char不相连，就更不用说如果还有其他重复char的情况了
            
            helper.push({cnt, key});// pair<int, char>居然有默认的函数?
        }
        
        // 为了保证两个字符不相连，每次取两个，这个操作万万没想到吧
        while (helper.size() >=2 ) {
            auto t1 = helper.top(); helper.pop();
            auto t2 = helper.top(); helper.pop();
            
            res.push_back(t1.second);
            res.push_back(t2.second);
            
            if (--(t1.first)) helper.push(t1);// 其实可以简化为if (--t1.first)
            if (--(t2.first)) helper.push(t2);
        }
        // 跳出while循环时，要不然helper为空，要不然helper只剩一个char，即一个pair；
        // 而且对于剩下一个pair的情况，其cnt个数比定等于1，如果大于1，说明不能organize，这会在第二个
        // for循环里面的if (cnt > (size+1)/2) 时返回
        if (helper.size()) res.push_back(helper.top().second);
        
        return res;
    }
};

int main(int argc, const char * argv[]) {
    Solution gua;
    string rtn;
    
    rtn = gua.reorganizeString("aab");
    cout << "expect value = \"aba\", actual value = " << rtn << endl;

    rtn = gua.reorganizeString("aaab");
    cout << "expect value = , actual value = " << rtn << endl;

    // 我就知道会有一个考察greedy的case，要错哇。。。
    rtn = gua.reorganizeString("baaba");
    cout << "expect value = \"ababa\", actual value = " << rtn << endl;

    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}


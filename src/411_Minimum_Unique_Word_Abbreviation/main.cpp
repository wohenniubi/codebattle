
#include <iostream>
#include <unordered_map>
#include <queue>

using namespace std;

class Solution {
public:
    #define MYTYPE pair<int,string> // 大意了大意啦，居然写成pair<int,int>了，debug半天
    struct myCmp {
        // 或者写成lambda函数
        bool operator()(MYTYPE &A, MYTYPE &B) const {
            return A.first > B.first;
        }
    };
    
    void backtrack(string &target, const string &path, int pos, int digits, int chars, int cnt, unordered_map<string, int> &tshorts) {
        // 返回条件, 例如: target="a", 1, a
        // 1: path="",  pos = 1, digits = 1, chars = 0, cnt = 0
        // a: path="a", pos = 1, digits = 0, chars = 1, cnt = 0
        if (pos == target.size()) {
            //path += (digits?to_string(digits):""); 已经定义为const了，所以不能这么搞
            string tmp = path + (digits?to_string(digits):"");
            tshorts[tmp] = chars + (digits?cnt+1:cnt);// 剩余的字符数+被压缩的字符分组数(cnt+1)
            return;// 会不会出现相同的压缩字符串，不同的lenght？
        }
        
        // 两种选择，压缩当前字符或者不压缩
        backtrack(target, path, pos+1, digits+1, chars, cnt, tshorts);
        backtrack(target, path+(digits?to_string(digits):"")+target[pos], pos+1, 0, chars+1, (digits?cnt+1:cnt), tshorts);
        return;
    }
    
    // 检查"3d"是不是"word"的缩写词
    bool isValidAbbreviation(string abbr, string pattern) {
        // 字符串比较了，双索引
        int lhs = 0, rhs = 0, num = 0;
        while (lhs < abbr.size() && rhs < pattern.size()) {
            if (isdigit(abbr[lhs])) {
                num = num*10 + (abbr[lhs] - '0');
                ++lhs;
                if (lhs == abbr.size())
                    rhs += num;
            } else {
                rhs += num;
                num = 0;// 别忘了清零呀
                if (rhs >= pattern.size())//但凡使用索引要注意别越界呀
                    break;
                if (abbr[lhs] != pattern[rhs])
                    return false;
                ++lhs; ++rhs;
            }
        }
        // 跳出循环时可能是其中一方不满足条件
        return lhs == abbr.size() && rhs == pattern.size();
    }
    
    string minAbbreviation(string target, vector<string>& dictionary) {
        vector<string> dict;
        for (auto &word : dictionary)
            // 出现了相同长度的字符串时，会与target的最短字符串重复，因此要把这些word记下来
            // 长度不相同的字符串，其压缩后的字符串必定与target不相同，因此不会影响target的最短压缩
            if (word.size() == target.size())
                dict.push_back(word);
        
        if (dict.empty())
            return to_string(target.size());
        
        // 先写出可能的组合吧，复习一下回溯问题
        unordered_map<string, int> tshorts;
        // string path = "";
        backtrack(target, "", 0, 0, 0, 0, tshorts);// 这里需要四个状态，已经填充好的path，当前执行到的位置，压缩的字符个数，保留的char个数，有几组数字（便于求length）
        
        // 再把target的压缩字符从最小长度开始与dict中word的压缩字符进行比较
        priority_queue<MYTYPE, vector<MYTYPE>, greater<MYTYPE>> words;
        //priority_queue<MYTYPE, vector<MYTYPE>, myCmp> words;
        //for (auto &[word, len] : dict_shorts) { 怎么这么大意！！！应该使用tshorts啊
        for (auto &[word, len] : tshorts) {
            words.push({len, word});//不同字符，相同len的情况前后没有关系
        }
       
        // 优化方法是将每个缩写词与dictionary的词进行比较 
        while (words.size()) {
            // if (!dict_shorts.count(words.top().second)) {
            //     // 找到最小的长度啦
            //     return words.top().second;
            // }
            // words.pop();
            bool exist = false;
            for (auto & pattern : dict) {                
                if (isValidAbbreviation(words.top().second, pattern)) {
                    exist = true;
                    break;
                }// 不能过早认为words.top就是所求，要把所有的pattern都处理一遍
            }
            if (!exist) {
                // 找到最小的长度啦
                return words.top().second;
            }
            words.pop();// 只要是跳出for循环就说明存在于dict，那么继续执行
        }
        return "";
    }
};

int main(int argc, const char * argv[]) {
    Solution gua;
    string rtn, target;
    vector<string> dictionary;
    
    rtn = gua.minAbbreviation(target = "apple", dictionary={"blade","plain","amber"});
    cout << "expect value = 1p3, actual value = " << rtn << endl;

    rtn = gua.minAbbreviation(target = "apple", dictionary={"blade"});
    cout << "expect value = a4, actual value = " << rtn << endl;

    return 0;
}

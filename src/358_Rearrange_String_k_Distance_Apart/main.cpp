#include <queue>
#include <iostream>
#include <unordered_map>

using namespace std;

class Solution {
    priority_queue<pair<int,char>> helper;
    unordered_map<char, int> dict;
    
public:
    string rearrangeString(string s, int k) {
        int size = s.size();
        string rtn;
        // 没有明确k的取值范围，有个case是s="a", k=0... 如果不处理的话下面的操作会超时
        //if (k==0) return (size>1)?"":s;//大意了，k=0意味着相同的字符紧挨着也没问题
        if (k==0) return s;
        
        // 首先完成统计
        for (auto lo : s) {
            ++dict[lo];
        }
        // 然后加入到最大堆里面
        for (auto & [key, cnt] : dict) {
            helper.push({cnt, key});
        }
        // 最后是构造string，注意跳出条件
        while (helper.size()) {
            vector<pair<int,char>> tmps;
            for (int i = 0; i < k; ++i) {
                if (helper.size()) {
                    // 从堆里面取一个char，然后增加到rtn里面
                    auto tmp = helper.top(); helper.pop();
                    rtn.push_back(tmp.second);
                    if (--tmp.first) tmps.push_back(tmp);
                } else {
                    // 说明出现了不能凑够最短距离k的情况
                    return (tmps.size())?"":rtn;
                }
            }
            for (auto tmp : tmps) helper.push(tmp);
        }// 应该是跳不出while循环的
        
        return rtn;
    }
};

int main() {
	Solution gua1, gua2, gua3;

	// test string 
	string str, rst;
  str = "aaabc";
	rst = gua1.rearrangeString(str, 3);
	cout << "expect value = \"\", actual value = " << rst.c_str() << endl;
	
  str = "aabbcc";
  rst = gua2.rearrangeString(str, 3);
	cout << "expect value = \"abcabc\", actual value = " << rst << endl;

	str = "aa";
	rst = gua3.rearrangeString(str, 0);
	cout << "expect value = \"aa\", actual value = " << rst.c_str() << endl;

  return 0;
}




#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
public:
    //Runtime: 8 ms, faster than 33.77%
    //Memory Usage: 10.6 MB, less than 63.04%
    vector<int> diffWaysToCompute(string input) {
        // 为了针对1+1+1+1+1+1这种特殊例子增加的memo
        unordered_map<string, vector<int>> dict;
        
        function<vector<int>(string)> merge = [&](string input) ->vector<int> {
            vector<int> rtn;
            if (input.empty()) return rtn;

            // 采用分治算法解决，就像merge sort，不过这个节点要merge多次
            for (int i = 0; i < input.size(); ++i) {
                if (!isdigit(input[i])) {
                    vector<int> lhs = diffWaysToCompute(input.substr(0,i));
                    vector<int> rhs = diffWaysToCompute(input.substr(i+1));

                    // 题目这个例子看来允许重复值 rtn =[-34, -14, -10, -10, 10]
                    for (int j = 0; j < lhs.size(); ++j) {
                        //for (int k = 0; k < rhs.size(); ++j) { 怎会如此大意？？
                        for (int k = 0; k < rhs.size(); ++k) {
                            switch(input[i]) {
                                case '+':
                                    rtn.push_back(lhs[j] + rhs[k]);
                                break;
                                case '-':
                                    rtn.push_back(lhs[j] - rhs[k]);
                                break;
                                case '*':
                                    rtn.push_back(lhs[j] * rhs[k]);
                                break;
                            }
                        }
                    }
                }
            }
            if (rtn.empty()) {
                // 如果rtn为空且能运行到这里，说明input本身是个数字
                // 不包含或者仅仅包含一个操作符号例如：2，或者-2，此时直接转换为int，很巧妙的操作
                // rtn.push_back(int(input)); 大意了，这是python的用法
                rtn.push_back(stoi(input));
            }
            return rtn;
        };
        
        return merge(input);
    }
};

ostream &operator<<(ostream &os, vector<int> &rtn) {
    os << "[";
    for (auto val : rtn) {
        os << val << ", ";
    }
    os << "]";
    return os;
}

int main(int argc, const char * argv[]) {
    Solution gua;
    vector<int> rtn;
    string input;
    
    rtn = gua.diffWaysToCompute(input = "2-1-1");
    cout << "expect result = [2,0], actual result = " << rtn << endl;
    
    rtn = gua.diffWaysToCompute(input = "2*3-4*5");
    cout << "expect result = [-34, -14, -10, -10, 10], actual result = " << rtn << endl;

    return 0;
}

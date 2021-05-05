
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    // exp信息被分为pos和st两部分，这个栈用于解决+和*的优先级
    //Runtime: 332 ms, faster than 73.71%
    //Memory Usage: 94.8 MB, less than 34.41%
    void backtrack(string &num, int pos,
                   long sum, long prev, int target,
                   const string &path, vector<string> &rtn) {
        //返回条件，当执行到num的结尾，同时sum等于target值
        if (pos == num.size()) {
            if (sum == target)
                rtn.push_back(path);
            return;
        }
        
        // 现在开始做选择，每次推进一位; 实际操作是把整体当作一个数，然后从结尾慢慢往回切
        for (int l = 1; l <= num.size() - pos; ++l) {
            string t = num.substr(pos, l);
            
            if (t[0] == '0' && t.size() > 1) break;// 这是为了应对00XX这样的字符串，不能把"00"当作0处理
            long n = std::stol(t);
            
            if (n > INT_MAX) break;// 这是为了应对超大的字符串num
            
            if (pos == 0) {
                backtrack(num, l, n, n, target, t, rtn); // 对于第0位要特殊处理，前面没有操作符，就是t
                continue;
            }
            
            // 这样当前截断的t要和先前的exp组成字符串，分为3种情况；乘法的处理tricky一点，prev保存的是单纯的一个数据，例如:2*3，或者2
            backtrack(num, pos + l, sum + n, n, target, path + '+' + t, rtn);
            backtrack(num, pos + l, sum - n, -n, target, path + '-' + t, rtn);
            backtrack(num, pos + l, sum - prev + prev*n, prev * n, target, path + '*' + t, rtn);
        }
        return;
    }
    
    vector<string> addOperators(string num, int target) {
        vector<string> rtn;
        // 想到回溯算法（状态+选择）再配合memo，硬算吧
        //
        // backtrack(num, 0, st, target, rtn); 这些状态还不够
        // long sum, prev;// 为了从path的表达式快速转换为值，保留上一节点的值和所有的值
        // char op = "";// 还要保存上一个操作，便于更新sum
        // 从pos这个位置开始，总共有n-1个空位，每个位置有3个选择
        // string path;// 为了存入rtn里面，要把path准备好
        backtrack(num, 0, 0, 0, target, "", rtn);
        return rtn;
    }
};

ostream &operator<<(ostream &os, vector<string> &rtn) {
    os << "[";
    for (auto &exp : rtn)
        os << exp << ", ";
    os << "]";
    return os;
}

int main(int argc, const char * argv[]) {
    Solution gua;
    int target;
    vector<string> rtn;
    string num;

    rtn = gua.addOperators(num = "00", target = 0);
    cout << "expect value = [0*0, 0+0, 0-0], actual value = " << rtn << endl;

    rtn = gua.addOperators(num = "123", target = 6);
    cout << "expect value = [1*2*3, 1+2+3], actual value = " << rtn << endl;

    rtn = gua.addOperators(num = "232", target = 8);
    cout << "expect value = [2*3*2, 2+3*2], actual value = " << rtn << endl;

    rtn = gua.addOperators(num = "3456237490", target = 9191);
    cout << "expect value = [], actual value = " << rtn << endl;

    return 0;
}

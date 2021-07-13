
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    // Runtime: 4 ms, faster than 66.60%
    // Memory Usage: 6.8 MB, less than 96.53%
    vector<string> restoreIpAddresses(string s) {
        // 感觉是得使用backtracking，复杂度指数级别，但是可以通过剪枝在实际操作时减少复杂度
        vector<string> rtn;
        vector<string> paths;
        if (s.size() > 12 || s.size() < 4) return rtn;

        // restoreIPs(s, path, 0, 0, 4, rtn);// 0, 0, 4分别表示：pos，当前值，剩余的'.'个数
        restoreIPs(s, paths, 0, rtn);
        return rtn;
    }
    
    void restoreIPs(string &s, vector<string> &paths, int pos, vector<string> &rtn) {
        // 返回条件TODO
        // if (pos == s.size() && cnt != 0) return;
        // if (pos < s.size() && cnt == 0) return;
        if (pos > s.size() || paths.size() > 4) return;// 因为上层采用pos+i，因此可能出现pos越界
        
        // 加入rtn的时刻，要取完所有的字符，且正好是4个字段
        if (pos == s.size() && paths.size() == 4) {
            rtn.push_back(paths[0] + "." + paths[1] + "." + paths[2] + "." + paths[3]);
            return;
        }
        
        // 这里是3个选项，截取1~3个字符，也就是三叉树
        for (int i = 1; i <=3; ++i) {
            string sub = s.substr(pos, i);
            // 合法性检查，空字符串，以0为开头，超过255，都不能处理
            if (sub.empty() || (sub.size()>1 && sub[0] == '0') || stoi(sub) > 255) continue;
            
            paths.push_back(sub);
            restoreIPs(s, paths, pos+i, rtn);
            paths.pop_back();
        }
    }
};

ostream & operator<< (ostream &os, vector<string> &rtn) {
    os << "[";
    for (auto & ip : rtn) {
        os << ip << ", ";
    }
    
    os << "]";
    return os;
}

int main(int argc, const char * argv[]) {
    Solution gua;
    
    vector<string> rtn;
    string s;

    rtn = gua.restoreIpAddresses(s = "101023");
    cout << rtn << endl;

    rtn = gua.restoreIpAddresses(s = "25525511135");
    cout << rtn << endl;

    rtn = gua.restoreIpAddresses(s = "010010");
    cout << rtn << endl;

    rtn = gua.restoreIpAddresses(s = "0000");
    cout << rtn << endl;
    
    rtn = gua.restoreIpAddresses(s = "1111");
    cout << rtn << endl;
    return 0;
}

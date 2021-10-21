
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    //Runtime: 16 ms, faster than 58.49%
    //Memory Usage: 11.6 MB, less than 79.47% 
    vector<string> subdomainVisits(vector<string>& cpdomains) {
        vector<string> rtn;
        unordered_map<string, int> memo;
        if (cpdomains.empty()) return rtn;
        
        // for (auto &cpdomain : dpdomains) { 笔误啊笔误啊！！！
        for (auto &cpdomain : cpdomains) {
            // 首先找到空格
            auto pos = cpdomain.find(' ');
            if (pos == string::npos) continue;
            
            int rep = stoi(cpdomain.substr(0, pos));
            string path = cpdomain.substr(pos+1);// 这会取出从空格下一个到最后的所有字符串
            memo[path] += rep;
            
            // 现在开始处理. 因为只需要处理剩余的subdomain，因此可以reuse pos
            //while ((pos = path.find(pos+1, '.')) != string::npos) { 大意了啊！！
            while ((pos = cpdomain.find('.', pos+1)) != string::npos) {
                // discuss.leetcode.com  pos = 0
                string subdomain = cpdomain.substr(pos+1);//path
                memo[subdomain] += rep;
            }
        }
        
        for (auto & [key, rep] : memo) {
            rtn.push_back(to_string(rep) + " " + key);
        }
        
        return rtn;
    }
};

int main(int argc, const char * argv[]) {
    Solution gua;
    vector<string> rtn, cpdomains;
   
    rtn = gua.subdomainVisits(cpdomains = {"9001 discuss.leetcode.com"});
    for (auto &item : rtn)
        cout << item << " " << endl;
    
    return 0;
}

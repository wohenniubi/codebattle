
#include <iostream>
#include <vector>
#include <unordered_set>
#include <queue>

using namespace std;

class Solution {
public:
    void rollOne(string & path, int pos, bool isUp) {
        char & digit = path[pos];
        if (isUp) {
            digit = (digit == '9')? '0': digit+1;
        } else {
            digit = (digit == '0')? '9': digit-1;
        }
        return;
    }
    //Runtime: 184 ms, faster than 71.56%
    //Memory Usage: 50.9 MB, less than 26.19%
    int openLock(vector<string>& deadends, string target) {
        if (target == "0000") return 0;
        
        unordered_set<string> dict; // (deadends)
        for (auto & deadend : deadends) dict.insert(deadend);
        
        deque<string> steps{"0000"};
        int cnt = 0;
        while (steps.size()) {
            int size = steps.size();
            cnt++;
            
            for (int i = 0; i < size; ++i) {
                string tmp = steps.front();
                steps.pop_front();
                
                if (dict.count(tmp)) continue;
                dict.insert(tmp);// 复用了一下dict哈希表
                
                if (tmp == target) return cnt-1;
                
                // 现在开始判断邻居，总共4个key，每个key有两个方向
                for (int j = 0; j < target.size(); ++j) {
                    // 向上roll
                    rollOne(tmp, j, 1);
                    //tmp不在deadends里，且没有被访问过，才会加入下一次计算的candidates
                    if (!dict.count(tmp)) // && !visited.count(tmp)
                        steps.push_back(tmp);
                    rollOne(tmp, j, 0);
                    
                    // 向下roll
                    rollOne(tmp, j, 0);
                    if (!dict.count(tmp)) // && !visited.count(tmp)
                        steps.push_back(tmp);
                    rollOne(tmp, j, 1);
                }
            }
        }
        
        return -1;
    }
};

int main(int argc, const char * argv[]) {
    Solution gua;
    vector<string> deadends;
    string target;
    int rtn;

    rtn = gua.openLock(deadends = {"8888"}, target = "0009");
    cout << "expect result = 1, actual result = " << rtn << endl;

    rtn = gua.openLock(deadends = {"0000"}, target = "8888");
    cout << "expect result = -1, actual result = " << rtn << endl;

    rtn = gua.openLock(deadends = {"8887","8889","8878","8898","8788","8988","7888","9888"}, target = "8888");
    cout << "expect result = -1, actual result = " << rtn << endl;
    return 0;
}

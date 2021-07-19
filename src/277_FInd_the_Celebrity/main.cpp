
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

unordered_map<string, bool> helper;

void createGraph(vector<vector<int>> &graph) {
    helper.clear();
    for (int i = 0; i < graph.size(); ++i) {
        for (int j = 0; j < graph[i].size(); ++j) {
            string key = to_string(i)+','+to_string(j);
            helper[key] = graph[i][j];
        }
    }
}

bool knows(int a, int b) {
    string key = to_string(a)+','+to_string(b);
    return helper[key];
}

class Solution {
public:
    //Runtime: 171 ms, faster than 32.73% 
    //Memory Usage: 9.7 MB, less than 25.16%
    int findCelebrity(int n) {
        // 这里的尽可能少调用knows，估计就是要让复杂度不要是O(n*n)
        
        int rtn = 0;// 先假定名人就是0，然后遍历其他所有的人去验证这个可能的名人
        // 这个for loop以可能的名人为出发点，一旦发现他认识其他人，那么就把另一个人作为名人
        for (int i = 1; i < n; ++i) {
            if (knows(rtn, i)) {
                rtn = i;
            }
        }
        // 以上代码简单，但是在循环过程中，所有的情况都检查到了
        // 如果rtn初始化为0，在最后一刻才被替换，那么0不认识[1,n-2]的人，所以排出0为名人，让n-1为名人
        // 然后还要再以n-1为名人，再遍历检查一次，因为还没有比较n-1是否认识[0,n-2]的人
        
        for (int i = 0; i < n; ++i) {
            if (rtn == i) continue;// 跳过自己一次
            
            if (knows(rtn, i) || !knows(i, rtn))
                return -1;// 假如1和n-1出现了情况，为什么不再检查除了2，n-2这些人是否为名人呢？
            // 因为先前的for loop，已经判断了0不认识2，如果2要是名人，那么0应该认识2，矛盾
            // 同理也可以知道2,n-2都不可能为名人，否则的话前面的for loop就已经替换rtn为[2,n-2]之间的数了
            // 因此不需要再做多余的判断，直接返回-1... 有点烧脑啊
        }
        return rtn;
    }
};

int main(int argc, const char * argv[]) {
    Solution gua;
    vector<vector<int>> graph;
    int rtn, n;
    
    createGraph(graph = {{1,1,0}, {0,1,0}, {1,1,1}});
    rtn = gua.findCelebrity(n = graph.size());
    cout << "expect value = 1, actual value = " << rtn << endl;
    
    createGraph(graph = {{1,0,1}, {1,1,0}, {0,1,1}});
    rtn = gua.findCelebrity(n = graph.size());
    cout << "expect value = -1, actual value = " << rtn << endl;

    return 0;
}


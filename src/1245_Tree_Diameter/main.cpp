
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    int maxPath;
    //Runtime: 44 ms, faster than 81.91%
    //Memory Usage: 21.3 MB, less than 60.30%
    int dfs(vector<vector<int>> &graph, int prev, int src, vector<int> &memo) {
        // 结束条件
        // if (memo[src]) return {memo[src], memo[src]};
        if (memo[src] != -1) {
            return maxPath = INT_MAX;//有环，直接返回
        }
        memo[src] = 0;// 最好这里初始化一下，可以区分这个src是否被访问过
        
        priority_queue<int,vector<int>,greater<int>> kids;
        
        for (auto adj : graph[src]) {
            if (adj == prev) continue;
            
            // 此时src就是root，adj就是叶子结点
            // auto [maxRoot, maxLeaf] = dfs(graph, src, adj, memo);
            int maxLeaf = dfs(graph, src, adj, memo);
            if (maxLeaf == INT_MAX) {
                return maxPath = INT_MAX;
            }
            // maxPath = max(maxPath, maxRoot);
            
            kids.push(1+maxLeaf);
            if (kids.size() > 2) kids.pop();
        }
            
        int sum = 0, leaf = 0;
        while (kids.size()) {
            sum += kids.top();
            leaf = max(leaf, kids.top());
            kids.pop();
        }
        
        maxPath = max(maxPath, sum);
        // memo[src] = maxPath;
        memo[src] = sum;
        return leaf; //return {sum, leaf};
    }
    
    int treeDiameter(vector<vector<int>>& edges) {
        // 貌似就是广度+深度遍历DFS，函数返回最深的path；之后使用一个memo存下来，然后供其他节点使用；这样一说又有点像dp
        maxPath = 0;
        
        // 还是先构建一个graph，这次是无向图，而且是稀疏图，因为节点个数是[0,len(edges)]，会不会有loop呢
        int size = edges.size();
        vector<vector<int>> graph = vector<vector<int>>(size+1);
        for (auto & edge: edges) {
            int u = edge[0], v = edge[1];
            graph[u].push_back(v);
            graph[v].push_back(u);
        }
        
        // vector<int> memo = vector<int>(size+1);// visited数组，同时也用于存储dp信息
        vector<int> memo = vector<int>(size+1, -1);// visited数组，同时也用于存储dp信息；还要区分已经访问过的末梢节点
        for (int i = 0; i <= size; ++i) {
            if (graph[i].empty()) continue;
            
            // 以当前node作为root进行dfs计算
            // if (memo[i] == 0) {
            if (memo[i] == -1) {
                dfs(graph, -1, i, memo); // 因为是无向图，要传入一个in path，便于跳过in path
                // rtn = max(rtn, maxPath);
            } // else 就不处理
        }
        return maxPath;
    }
};

int main(int argc, const char * argv[]) {
    Solution gua;
    int rtn;
    vector<vector<int>> edges;
    rtn = gua.treeDiameter(edges={{0,1},{0,2},{1,2}});
    cout << "expect value = INT_MAX, actual value = " << (rtn==INT_MAX? "INT_MAX": to_string(rtn)) << endl;

    rtn = gua.treeDiameter(edges={{0,1},{0,2}});
    cout << "expect value = 2, actual value = " << rtn << endl;

    rtn = gua.treeDiameter(edges={{0,1},{1,2},{2,3},{1,4},{4,5}});
    cout << "expect value = 4, actual value = " << rtn << endl;

    return 0;
}

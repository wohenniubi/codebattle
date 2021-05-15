
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    class UnionFound {
    public:
        int num;
        vector<int> parents;
        
        UnionFound(int n) {
            num = n;
            parents = vector<int>(n);
            for (int i = 0; i < n; ++i)
                //parents[i] = n;// 怎么这么大意！！！
                parents[i] = i;// 怎么这么大意！！！
        }
        
        int find(int id) {
            while (parents[id] != id) {
                parents[id] = parents[parents[id]];
                id = parents[id];
            }
            return id;
        }
        
        void merge(int ida, int idb) {
            int pa = find(ida);
            int pb = find(idb);
            if (pa != pb) {
                parents[pb] = pa;
                --num;// 独立的点减少了1个
            }
            return;
        }
    };
    
    //Runtime: 16 ms, faster than 92.58%
    //Memory Usage: 11.9 MB, less than 95.69%
    int countComponents(int n, vector<vector<int>>& edges) {
        // 感觉像是union found，因为n是确定的，所以应该大方向对
        UnionFound helper(n);
        for (auto & edge : edges) {
            int ai = edge[0], bi = edge[1];
            helper.merge(ai, bi);
        }
        // 如果完全都是孤立的点，说明没有联通
        // return (n == helper.num)? 0 : helper.num;
        return helper.num;// 1 [] 需要返回1
    }
};

int main(int argc, const char * argv[]) {
    Solution gua;
    int rtn, n;
    vector<vector<int>> edges;
    rtn = gua.countComponents(n = 1, edges={});
    cout << "expect value = 1, actual value = " << rtn << endl;

    rtn = gua.countComponents(n = 5, edges={{0,1},{1,2},{3,4}});
    cout << "expect value = 2, actual value = " << rtn << endl;
    
    rtn = gua.countComponents(n = 5, edges={{0,1},{1,2},{2,3},{3,4}});
    cout << "expect value = 1, actual value = " << rtn << endl;

    return 0;
}


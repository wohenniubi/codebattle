
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    // 方法3：在2的基础上改进vector，应对稀疏数组情况下对内存的占用
    //Runtime: 4 ms, faster than 52.21%
    //Memory Usage: 7.6 MB, less than 30.36%
    void find(unordered_map<int, int> &memo, int id1, int id2) {
        int minId = min(id1, id2), maxId = max(id1, id2);
        if (minId == maxId) return; // 就不做操作
        
        // 限制映射表都是用小的组ID到大的组ID
        if (memo.count(minId)) {
            find(memo, memo[minId], maxId);// 找到的话，继续比较两者是不是一样
        } else {
            // 没有找到的话，增加一个映射;
            memo[minId] = maxId;
        }
    }
    
    int minSwapsCouples(vector<int>& row) {
        unordered_map<int, int> memo;
        
        for (int i = 0; i < row.size(); i+= 2) {
            find(memo, row[i]/2, row[i+1]/2);
        }
        
        return memo.size();
    }
    
    // 方法2；采用了union find的思路，实在不知道是如何证明的
    //Runtime: 0 ms, faster than 100.00%
    //Memory Usage: 7.3 MB, less than 82.25%
    class UnionFind {
        vector<int> parents;
    public:
        UnionFind(int n) {
            parents.resize(n);
            for (int i = 0; i < n; ++i)
                parents[i] = i;
        }
        
        int find(int id) {
            //int gid = id/2;
            while (parents[id] != id) {
                parents[id] = parents[parents[id]];
                id = parents[id];
            }
            return id;
        }
        
        void unite(int id1, int id2) {
            int p1 = find(id1), p2 = find(id2);
            if (p1 != p2)
                parents[p1] = p2;
        }
    };
    
    int minSwapsCouples2(vector<int>& row) {
        int rtn = 0, size = row.size();
        UnionFind memo(size/2);
        
        for (int i = 0; i < size; i+=2) {
            //if (row[i]/2 == row[i+1]/2) continue;// 大意了，此时不能再用原来的group id，要用union find里面的
            if (memo.find(row[i]/2) == memo.find(row[i+1]/2)) continue;
            ++rtn;
            memo.unite(row[i]/2, row[i+1]/2);
        }
        
        return rtn;
    }
    
    //Runtime: 0 ms, faster than 100.00%
    //Memory Usage: 7.4 MB, less than 56.51%
    // 先使用Greedy做法，从左到右，每次找一个数字的配对数字，时间复杂度O(n^2)
    int minSwapsCouples1(vector<int>& row) {
        int size = row.size();
        int rtn = 0;
        
        // 每次跳跃检查，对于匹配到的数字对，就不做操作
        for (int i = 0; i < size; i+= 2) {
            //if (row[i]^1 == row[i+1]) continue; 超级大意啊！优先级优先级
            if ((row[i]^1) == row[i+1]) continue;
            
            ++rtn;
            // 不匹配的话，开始从i+2找匹配的数字，由于是从左到右，所以左边必定是已经完成排序的
            for (int j = i+2; j < size; ++j) {
                //if (row[i]^1 != row[j]) continue;
                if ((row[i]^1) != row[j]) continue;
                
                swap(row[i+1], row[j]);
                break;
            }
            // 由于配对数字必定存在于row里面，所以for loop必定可以找到
        }
        
        return rtn;
    }
};

int main(int argc, const char * argv[]) {
    Solution gua;
    vector<int> row;
    int rtn;
    
    rtn = gua.minSwapsCouples(row = {2,0,5,4,3,1});
    cout << "expect value = 1, actual value = " << rtn << endl;

    rtn = gua.minSwapsCouples(row = {3,2,0,1});
    cout << "expect value = 0, actual value = " << rtn << endl;

    rtn = gua.minSwapsCouples(row = {0,2,1,3});
    cout << "expect value = 1, actual value = " << rtn << endl;

    return 0;
}

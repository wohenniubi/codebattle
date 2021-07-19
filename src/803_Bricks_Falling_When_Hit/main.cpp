
#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
public:
    // 方法2:采用UnionFind，不过为了统计数据，除了父节点数组之外，还需要增加组群个数数组
    // 另外为了找到是否为stable的状态，还需要一个数组t；其他思路保持不变，也是倒着检查的桥砖的
    vector<int> hitBricks2(vector<vector<int>>& grid, vector<vector<int>>& hits) {
        int m = grid.size(), n = grid[0].size(), k = hits.size();
        vector<int> rtn(k);//初始化为0，没毛病
        
        vector<int> root(m*n, -1), adjs(m*n, 1), stable(m*n, 0);
        // root表示parent数组，降纬度；adjs是某个[x,y]坐标为root时的组群数组，stable是某个坐标[x,y]的状态数组，1表示stable
        
        for (int i = 0; i < k; ++i)
            grid[hits[i][0]][hits[i][1]]--; // 先敲掉，看到最后稳定的状态
        for (int j = 0; j < n; ++j)
            stable[j] = 1;// 把第一行的所有位置的状态都设置为stable，不管是否存在砖块
        
        // 然后从最终状态开始，搜集union find信息，由于是从左到右，从上到下，因此每个位置都值需要判断右方邻居和下方临居
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] != 1) continue;// 砖都没有，就没必要处理root和count了
                
                int parent = find(root, i*n+j);
                
                // 当前位置有砖，那么判断其右方和下方是否存在砖块，目的是构造组群、统计个数以及更新stable状态
                if ((j+1 < n) && grid[i][j+1] == 1) {
                    int head = find(root, i*n + j+1);
                    // 固定把邻居加到[i,j]组群
                    if (parent != head) {
                        root[head] = parent; adjs[parent] += adjs[head];//非常精妙，都会累加到parent上面去
                        // 也正因为如此，如果还是四方判断的话，会重复加入，故认为左上角都稳定了，仅判断右方和下方
                        stable[parent] = stable[head] = (stable[head] | stable[parent]);
                    }
                }
                if ((i+1 < m) && grid[i+1][j] == 1) {
                    int head = find(root, (i+1)*n + j);
                    if (parent != head) {
                        root[head] = parent; adjs[parent] += adjs[head];
                        stable[parent] = stable[head] = (stable[head] | stable[parent]);
                    }
                }
            }
        }
        
        // 还是倒着从后往前加入敲掉的砖块，每加入一次，检查上下左右的邻居：1）是否可以与[x,y]达到stable，2）是否可以构成组群
        for (int i = k-1; i >= 0; --i) {
            int x = hits[i][0], y = hits[i][1];
            int cnt = 0;//为了更新[x,y]所在组群的个数
            if (++grid[x][y] != 1) continue;
            
            int parent = find(root, x*n + y);// 那些被敲掉的点，刚补上的时候parent应该是自己
            // hits[i]正好是敲掉砖的那一次
            for (auto & dir : dirs) {
                int tmpx = x + dir.first, tmpy = y + dir.second;
                // 搜集每一方的邻居时要进行坐标合法性检查
                if (tmpx < 0 || tmpx >= m || tmpy < 0 || tmpy >= n || grid[tmpx][tmpy] != 1)
                    continue;

                int head = find(root, tmpx * n + tmpy);
                if (parent == head) continue;// 认为统计过了
                
                if (!stable[head]) cnt += adjs[head];// 这一步的操作是什么意思？？
                // 倒着补砖时，如果敲掉[x,y]之前邻居是孤立的，那么这个邻居及其组群个数就属于drop的点，因此需要积累一下
                // 不+1因为不包含被敲掉的砖
                
                // 然后把邻居的组群信息修改为[x,y]
                root[head] = parent; adjs[parent] += adjs[head];
                stable[parent] = stable[head] = (stable[parent] | stable[head]);
            }
            
            // 完成一个点的处理之后，仅仅在[x,y]稳定的情况下，才能使用积累的cnt进行更新，
            if (stable[parent]) rtn[i] = cnt;//
        }
        
        return rtn;
    }
    vector<pair<int,int>> dirs{{0,1},{1,0},{0,-1},{-1,0}};
    
    int find(vector<int> &root, int pos) {
        // 由于root里面的值可能是-1，故不能使用压缩路径的做法，且不能使用while(pos != root[pos])的条件
        return (root[pos] == -1)? pos: find(root, root[pos]);
    }
    
    //Runtime: 332 ms, faster than 67.18%
    //Memory Usage: 118.1 MB, less than 42.03%
    // 忘记怎么做了，看答案吧；方法1:用的是DFS+哈希表，每次敲完砖之后比较前后的砖，就可以知道掉落的砖
    vector<int> hitBricks(vector<vector<int>>& grid, vector<vector<int>>& hits) {
        int m = grid.size(), n = grid[0].size(), k = hits.size();
        vector<int> rtn(k);//初始化为0，没毛病
        unordered_set<int> noDrops;
        
        // 因为是倒着思考，首先把grid里面的砖去掉
        for (int i = 0; i < k; ++i)
            grid[hits[i][0]][hits[i][1]] -= 1;
        
        // 然后对第一行的所有列进行DFS检查，搜集hits之后，还剩余的砖，这样的话，就避免对那些中途掉落的砖进行逐一统计
        for (int j = 0; j < n; ++j)
            if (grid[0][j] == 1) // 因为可能出现在某个位置重复敲击，所以可能小于-1，故不能用grid[i][j] != 0
                dfscheck(grid, 0, j, noDrops);
        
        // 搜集完了noDrops信息（最终stable的砖），再来一个循环，从后往前补上每一个被敲掉的砖。要前后比较
        for (int i = k-1; i >= 0; --i) {
            int oldSize = noDrops.size();
            int x = hits[i][0], y = hits[i][1];
            
            // 补上一块砖之后还是亏的，说明敲掉的这个位置先前还被敲过，那么之后再敲，不会影响掉落的砖的个数
            // 即掉落为0，这正好与rtn[i]的初始化值保持一致，完全没有毛病
            if (++grid[x][y] != 1) continue;
            
            // 检查加入位置的上下左右是否是稳定的(存在于noDrops中)，如果存在，那么需要
            if ((x-1>=0 && noDrops.count((x-1)*n + y))
                || (x+1<m && noDrops.count((x+1)*n + y))
                || (y-1>=0 && noDrops.count(x*n + (y-1)))
                || (y+1<n && noDrops.count(x*n + (y+1)))
                || x == 0) { //超级大意啊！！！还有x == 0的情况，此时不需要判断邻居是否stable，自己就很stable
                
                // 然后把这个位置加到noDrop中去，这样i-2次补砖时看到的状态的到了更新
                //noDrops.insert(x*n + y); // 别大意啊，不仅加入那一块砖，还要从那个位置DFS遍历一遍
                dfscheck(grid, x, y, noDrops);// 由于那些因为不stable而掉落的砖，还没有加入到noDrops里面
                
                // 要在if里面才能计算啊！！！
                int newSize = noDrops.size();
                rtn[i] = newSize - oldSize - 1;// 减去1是那块被敲掉的砖，它不属于drop的砖
            }
            // int newSize = noDrops.size();
            // rtn[i] = newSize - oldSize - 1;// 减去1是那块被敲掉的砖，它不属于drop的砖
        }
        
        return rtn;
    }
    
    // 这里的check本质上是个DFS的遍历
    void dfscheck(vector<vector<int>>& grid, int i, int j, unordered_set<int>& noDrops) {
        int m = grid.size(), n = grid[0].size();
        int key = i*n +j;
        if (i < 0 || i >= m || j < 0|| j >= n|| grid[i][j] != 1 || noDrops.count(key))
            return;
        
        noDrops.insert(key);//合法性判断之后加入noDrop(即visited数组)
        
        // 然后检查四周的砖块，因为有noDrops的anti重复访问，这里可以直接写成四个方向
        dfscheck(grid, i, j+1, noDrops);
        dfscheck(grid, i+1, j, noDrops);
        dfscheck(grid, i, j-1, noDrops);
        dfscheck(grid, i-1, j, noDrops);
    }
};

ostream &operator<<(ostream &os, vector<int> &rtn) {
    os << "[";
    for (auto val : rtn)
        os << val << ", ";
    os << "]";
    return os;
}

int main(int argc, const char * argv[]) {
    Solution gua;
    vector<vector<int>> grid, hits;
    vector<int> rtn;

    rtn = gua.hitBricks(grid = {{1},{1},{1},{1},{1}}, hits = {{3,0},{4,0},{1,0},{2,0},{0,0}});
    cout << "expect result = [1,0,1,0,0], actual result = " << rtn << endl;

    rtn = gua.hitBricks(grid = {{1,0,0,0},{1,1,1,1}}, hits = {{1,0}});
    cout << "expect result = [3], actual result = " << rtn << endl;

    rtn = gua.hitBricks(grid = {{1,0,0,0},{1,1,0,0}}, hits = {{1,1}, {1,0}});
    cout << "expect result = [0, 0], actual result = " << rtn << endl;

    return 0;
}

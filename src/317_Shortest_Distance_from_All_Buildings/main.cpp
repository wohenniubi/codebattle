
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    vector<pair<int,int>> dirs{{0,1},{-1,0},{0,-1},{1,0}};
    
    // 不修改grid的方法无法应对[1,0,1,0,1]的情况，还是得使用上面的方法，核心思想是把visit数组和grid合并
    // 并且每次使用var来检测某个位置是否可以被building访问，很tricky，巧妙的利用building和block是正数，于是用0和负数代表可达
    //Runtime: 24 ms, faster than 74.03% 
    //Memory Usage: 26.3 MB, less than 45.42%
    int shortestDistance(vector<vector<int>>& grid) {
        // 因为是求最短距离，因此肯定是BFS，但是如何巧妙的计算叠加的距离
        // 而且如何将visit数组与原本的grid数组合并在一起，很tricky
        int rtn = INT_MAX;
        int m = grid.size(), n = grid[0].size();
        vector<vector<int>> sum(m,vector<int>(n));// 肯定要计算每个building到i,j位置的距离叠加

        // 原本打算把building全部搜集起来，然后再做层序，好像不行；
        // 还是老老实实从每个building开始做遍历吧
        int var = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                // 找到一个building，从它开始做BFS
                if (grid[i][j] == 1) {
                    rtn = INT_MAX;// 以building作为root，开始BFS
                    //vector<vector<int>> visit(m,vector<int>(n));
                    vector<vector<int>> dist(m,vector<int>(n));
                    deque<pair<int,int>> st{{i,j}};
                    //visit[i][j] = 1;
                    while (st.size()) {
                        int size = st.size();
                        for (int k = 0; k < size; ++k) {
                            auto [x, y] = st.front();
                            st.pop_front();
                            //visit[x][y] = 1;
                            
                            for (auto &dir : dirs) {
                                int tx = x+dir.first, ty = y+dir.second;
                                // 坐标要合法，同时是可行的路，使用INT_MAX来区分不可达
                                //if (tx < 0 || tx >= m || ty < 0 || ty >= n || grid[tx][ty] != 0 || visit[tx][ty] == 1) {
                                if (tx < 0 || tx >= m || ty < 0 || ty >= n || grid[tx][ty] != var) {
                                    continue;
                                }
                                st.push_back({tx, ty});// 别那么大意啊，把tx,ty加入到deque里面
                                //visit[tx][ty] = 1;//此时就要加上，防止在计算过程中就出现重复
                                --grid[tx][ty];
                                dist[tx][ty] = dist[x][y] + 1;
                                sum[tx][ty] += dist[tx][ty];//sum[tx][ty]; 怎么这么大意！！
                                rtn = min(rtn, sum[tx][ty]);// 同时还要保留某个定点到[tx,ty]这个位置的最大值
                            }
                        }
                    }
                    --var;//更新level层数
                    //if (rtn == INT_MAX) return -1;
                }
            }
        }
        // 对于不可到达的情况，用rtn是否更新就可以判断出来
        // 因为rtn在每找到一个build时就会被初始化，然后一旦出现可行的位置就会更新，没更新说明没有找到可以更新的位置
        return (rtn == INT_MAX)?-1:rtn;
    }
};

int main(int argc, const char * argv[]) {
    Solution gua;
    int rtn;
    vector<vector<int>> grid;
    rtn = gua.shortestDistance(grid = {{1,0,1,0,1}});
    cout << "expect value = -1, actual value = " << rtn << endl;
    
    rtn = gua.shortestDistance(grid = {{0,2,1}, {1,0,2}, {0,1,0}});
    cout << "expect value = -1, actual value = " << rtn << endl;
    
    rtn = gua.shortestDistance(grid = {{1,0,2,0,1}, {0,0,0,0,0}, {0,0,1,0,0}});
    cout << "expect value = 7, actual value = " << rtn << endl;

    return 0;
}

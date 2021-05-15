
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

#define MYTYPE tuple<int,int,int>

struct myCmp {
    // 这里的MYTPE包含了height和x，y的坐标，其中height是因为每次要取最低的点，x和y是因为要从这个点向四周延伸
    bool operator()(MYTYPE &A, MYTYPE &B) {
        int hA = get<0>(A), hB = get<0>(B);
//        auto & [hA, std::ignore, std::ignore] = A;
//        auto & [hB, std::ignore, std::ignore] = B;
        return hA > hB;
    }
};

class Solution {
public:
    //Runtime: 56 ms, faster than 64.62%
    //Memory Usage: 14.5 MB, less than 36.31%
    vector<pair<int,int>> dirs{{0,1},{-1,0},{0,-1},{1,0}};
    int trapRainWater(vector<vector<int>>& heightMap) {
        if (heightMap.empty() || heightMap[0].empty())
            return 0;
        int row = heightMap.size(), col = heightMap[0].size();
        
        // 非常霸气的一道题，虽然是遍历图，但是完全没思路
        // 解决方法是用priority queue来引领BFS
        priority_queue<MYTYPE, vector<MYTYPE>, myCmp> candies;
        
        // 先便利四周的点，加入到candies里；图遍历中常用一个visit
        
        vector<vector<bool>> visit(row, vector<bool>(col));
        for (int i = 0; i < row; ++i) {
            candies.push({heightMap[i][0], i, 0});
            visit[i][0] = true;
            candies.push({heightMap[i][col-1], i, col-1});//别大意啊col-i
            visit[i][col-1] = true;
        }
        for (int j = 1; j < col-1; ++j) {
            candies.push({heightMap[0][j], 0, j});
            visit[0][j] = true;
            candies.push({heightMap[row-1][j], row-1, j});
            visit[row-1][j] = true;
        }
        
        int rtn = 0;// 现在开始计算储水
        while (candies.size()) {
            auto [h, x, y] = candies.top();
            candies.pop();
            
            // 查找它的邻居
            for (auto &dir : dirs) {
                int tx = dir.first + x, ty = dir.second + y;
                
                if (tx < 1 || tx >= row-1 || ty < 1 || ty >= col-1 || visit[tx][ty])
                    continue;
                
                rtn += max(0, h-heightMap[tx][ty]);// 如果h < height[tx][ty]，说明不能够储水
                candies.push({max(h, heightMap[tx][ty]), tx, ty});// 放入candies的点，相当于是把较低的位置都填平了
                // 之所以这样做正确，是因为priority queue保证height是逐渐变高的，就相当于海平面上升的方法
                visit[tx][ty] = true;// 每当加入container时才更新visit
            }
        }
        return rtn;
    }
};

int main(int argc, const char * argv[]) {
    Solution gua;
    int rtn;
    vector<vector<int>> heightMap;
    
    rtn = gua.trapRainWater(heightMap = {{1,4,3,1,3,2},{3,2,1,3,2,4},{2,3,3,2,3,1}});
    cout << "expect value = 4, actual value = " << rtn << endl;
    
    rtn = gua.trapRainWater(heightMap = {{3,3,3,3,3},{3,2,2,2,3},{3,2,1,2,3},{3,2,2,2,3},{3,3,3,3,3}});
    cout << "expect value = 10, actual value = " << rtn << endl;
    return 0;
}

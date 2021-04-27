
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

struct myHash {
    size_t operator() (const pair<int,int> &A) const {
        return hash<int>()(A.first) ^ hash<int>()(A.second);
    }
};

class Solution {
public:
    int gcd(int m, int n) {
        return (n == 0)? m: gcd(n, m%n);
    }
    
    pair<int,int> getRate(int xi, int yi, int xj, int yj) {
        // 为了避免水平线和垂直线
        if (xi == xj) {
            return {xi, 0}; // 垂直线
        }
        if (yi == yj) {
            return {0, yi}; // 水平线
        }
        
        // 对于其他情况，为了防止float数的比较，直接用整数来表示，不过就要用到取最大公约数
        // 计算斜率等于 delta_y / delta_x
        int delta_y = yj - yi, delta_x = xj - xi;
        int d = gcd(delta_y, delta_x);
        return {delta_y/d, delta_x/d};
    }
    
    //Runtime: 4 ms, faster than 99.37%
    //Memory Usage: 8.9 MB, less than 61.51%
    int maxPoints(vector<vector<int>>& points) {
        // 暴力求解，时间复杂度O(n^2)
        int size = points.size();
        if (size < 3) return size; // 两点必然在一条直线上
        
        int rtn = 0;
        
        // 要看每个点与其他点构成的直线，然后由于AB直线和BA直线是一样的，所以内层循环时不能重复先前的点
        for (int i = 0; i < size-1; ++i) {
            unordered_map<pair<int,int>, int, myHash> memo;
            // 这里是把斜率当作key，value是某个斜率的出现次数，同时要注意重复点的情况，不算斜率，单独处理
            int samepoints = 1, maxpoints = 0;// 只有自己时，初始化为一个点
            
            //auto [xi, yi] = {points[i][0], points[i][1]};
            int xi = points[i][0], yi = points[i][1];
            for (int j = i+1; j < size; ++j) {
                //auto [xj, yj] = {points[j][0], points[j][1]};
                int xj = points[j][0], yj = points[j][1];
                
                if (xi == xj && yi == yj) {
                    ++samepoints;
                } else {
                    pair<int,int> rate = getRate(xi, yi, xj, yj);
                    memo[rate]++;
                    // maxpoints = max(maxpoints, memo[rate] + samepoints); 不要在这里加samepoint，让操作不方便
                    maxpoints = max(maxpoints, memo[rate]);
                }
            }
            rtn = max(rtn, maxpoints + samepoints);// 很巧妙，拆成了两部分，代码很简洁
        }
        return rtn;
    }
};

int main(int argc, const char * argv[]) {
    Solution gua;
    int rtn;
    vector<vector<int>> points;
    rtn = gua.maxPoints(points = {{1,1},{3,2},{5,3},{4,1},{2,3},{1,4}});
    std::cout << "expect value = 4, actual value = " << rtn << endl;

    rtn = gua.maxPoints(points = {{1,1},{2,2},{3,3}});
    std::cout << "expect value = 3, actual value = " << rtn << endl;

    return 0;
}


#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    //Runtime: 8 ms, faster than 67.18%
    //Memory Usage: 9.1 MB, less than 24.43%
    int minTotalDistance(vector<vector<int>>& grid) {
        // 这不就是routing吗？不过由于不是求那个最小值的点，而仅仅是求manhattan距离，因此可以利用xy相互独立来转化
        // D = |x1-x| + |x2-x| + ... |xn -x| + |y1-y| + |y2-y| + ... |yn -y|
        // 可以转化为x = argmin(|x1-x| + |x2-x| + ... |xn -x|)
        // y = argmin(|y1-y| + |y2-y| + ... |yn -y|)，然后有个结论，x和y就是median
        vector<int> xs, ys;
        for (int i = 0; i < grid.size(); ++i) {
            for (int j = 0; j < grid[i].size(); ++j) {
                if (grid[i][j] == 1) {
                    xs.push_back(i);
                    ys.push_back(j);
                }
            }
        }
        sort(begin(xs), end(xs));
        sort(begin(ys), end(ys));
        int size = xs.size();
        int x = xs[size/2], y = ys[size/2];// 对于偶数长度的序列，中间两个都可以，所以默认取小的那个来计算后面的距离
        int sum = 0;
        for_each(begin(xs), end(xs), [&sum, &x](int i) {sum+= abs(x - i);});
        for_each(begin(ys), end(ys), [&sum, &y](int i) {sum+= abs(y - i);});
        return sum;
        
        // 注意可能的followup：（1）如果这些frieds有权重怎么计算距离；（2）如果必须要求x是序列xs中的某一个时怎么计算
    }
};

int main(int argc, const char * argv[]) {
    Solution gua;
    int rtn;
    vector<vector<int>> grid;
    rtn = gua.minTotalDistance(grid={{1,1}});
    cout << "expect value = 1, actual value = " << rtn << endl;

    rtn = gua.minTotalDistance(grid={{1,0,0,0,1},{0,0,0,0,0},{0,0,1,0,0}});
    cout << "expect value = 6, actual value = " << rtn << endl;

    rtn = gua.minTotalDistance(grid={{1,0,0,0,0,0,1},{0,0,0,0,0,0,0},{0,0,0,1,0,0,0}});
    cout << "expect value = 8, actual value = " << rtn << endl;
    return 0;
}


#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<pair<int,int>> dirs{{0,1},{-1,0},{0,-1},{1,0}};// 四个方向，北，西，南，东
    
    // Runtime: 0 ms, faster than 100.00%
    // Memory Usage: 5.9 MB, less than 87.44%
    bool isRobotBounded(string instructions) {
        // 标准解法是，（1）如果指令结束之后回到了原点，或者是（2）指令结束之后头朝向和最初的方向不同，则一定是个圈;
        // 对于(1)的理解，回到了原点，即使朝向与原来的方向不同，再重复1到3次就一定会朝向北边；
        // 对于(2)的理解，如果朝向和原方向相反，那么2倍的指令就可以回到原点；如果朝向和原方向垂直，那么4倍的指令可以回到原点
        int size = instructions.size();
        // auto [x, y, d] = make_tuple(0,0,0);
        int x = 0, y = 0, d = 0;
        
        for (int i = 0; i < size; ++i) {
            if (instructions[i] == 'G') {
                x += dirs[d].first;
                y += dirs[d].second;
                // rtn.second += 1;
            } else if (instructions[i] == 'L') {
                d = (d+1)%4;
            } else {
                // (instructions[i] == 'R');
                // d = (d-1)%4; C++里面的mod不要大意啊，可能为负值负值
                d = (d+3)%4;
            }
        }
        return (x==0 && y==0) || (d != 0);
    }
    
    tuple<int,int,int> program(string &instrctions, int n) {
        // pair<int,int> rtn{0,0};
        auto [x, y, d] = make_tuple(0,0,0);
        
        int dir = 0;
        while (n) {
            int size = instrctions.size();
            for (int i = 0; i < size; ++i) {
                if (instrctions[i] == 'G') {
                    x += dirs[d].first;
                    y += dirs[d].second;
                    // rtn.second += 1;
                } else if (instrctions[i] == 'L') {
                    d = (d+1)%4;
                } else {
                    // (instrctions[i] == 'R');
                    // d = (d-1)%4; C++里面的mod不要大意啊，可能为负值负值
                    d = (d+3)%4;
                }
            }
            --n;
        }
        
        return {x, y, d};//rtn;
    }
    
    // 超时？？尼玛限制得那么严格吗
    // Runtime: 4 ms, faster than 8.36%
    // Memory Usage: 6 MB, less than 66.20%
    bool isRobotBounded1(string instructions) {
        // 我的直观猜测是最迂指令x2，或者x4之后，坐标可以回到0,0，则说明是个环
        int x, y, d;
        // tuple<int,int,int> rtn = program(instructions, 2);
        tie(x,y,d) = program(instructions, 2);
        // if (rtn.first == 0 && rtn.second == 0)
        if (x == 0 && y == 0 && d == 0)
            return true;
        
        // pair<int,int> rtn = program(instructions, 4);
        tie(x,y,d) = program(instructions, 4);
        // if (rtn.first == 0 && rtn.second == 0)
        if (x == 0 && y == 0 && d == 0)
            return true;
        
        return false;
    }
};

int main(int argc, const char * argv[]) {
    Solution gua;
    bool rtn;
    string instructions;

    rtn = gua.isRobotBounded(instructions = "GLRLGLLGLGRGLGL");
    cout << "expect value = 1, actual value = " << rtn << endl;

    rtn = gua.isRobotBounded(instructions = "GGLLGG");
    cout << "expect value = 1, actual value = " << rtn << endl;

    rtn = gua.isRobotBounded(instructions = "GL");
    cout << "expect value = 1, actual value = " << rtn << endl;

    rtn = gua.isRobotBounded(instructions = "GG");
    cout << "expect value = 0, actual value = " << rtn << endl;

    return 0;
}

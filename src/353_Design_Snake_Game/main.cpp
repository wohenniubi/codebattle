
#include <iostream>
#include <queue>
#include <vector>
#include <unordered_set>
#include <unordered_map>

using namespace std;

class SnakeGame {
public:
    /** Initialize your data structure here.
        @param width - screen width
        @param height - screen height
        @param food - A list of food positions
        E.g food = [[1,1], [1,0]] means the first food is positioned at [1,1], the second is at [1,0]. */
    deque<pair<int,int>> body;
    unordered_map<string, pair<int,int>> dirs{{"U",{-1,0}},{"L",{0,-1}},{"R",{0,1}},{"D",{1,0}}};// Up, left, right, down
    unordered_set<int> memo;
    int row, col;
    // unordered_set<int> meat;// 理解错了，同一时间只有一块肉
    vector<vector<int>> meat;
    
    //Runtime: 128 ms, faster than 58.54%
    //Memory Usage: 61.8 MB, less than 69.65%
    SnakeGame(int width, int height, vector<vector<int>>& food) {
        // 感觉就是个图的遍历，只不过要多增加一些数据结构来维持蛇的身体，还要判断是否撞到自己
        memo.clear();
        memo.insert(0);
        body = {{0,0}};
        //row = width; col = height; 大意啦，写反了
        row = height; col = width;
        // 还得把食物位置记下来
        meat = food;
        reverse(begin(meat), end(meat));
//        for (auto & item : food)
//            meat.insert(item[0]*col+item[1]);
    }
    
    /** Moves the snake.
        @param direction - 'U' = Up, 'L' = Left, 'R' = Right, 'D' = Down
        @return The game's score after the move. Return -1 if game over.
        Game over when snake crosses the screen boundary or bites its body. */
    int move(string direction) {
        auto [x, y] = body.back();
        
        // 新的位置基于x,y还有direction
        int tx = x + dirs[direction].first, ty = y + dirs[direction].second;
        if (tx < 0 || tx >= row || ty < 0 || ty >= col)
            return -1;
        
        // 遇到肉和没有遇到肉的处理
        int pos = tx*col + ty;
        //if (meat.back()[0] == tx && meat.back()[1] == ty) { // 大意啦，还要注意meat不要为空！！！
        if (meat.size() && meat.back()[0] == tx && meat.back()[1] == ty) {
            // 可以认为是尾部不会减少;
            body.push_back({tx, ty});
            memo.insert(pos);
            meat.pop_back();//meat.erase(pos);
            return body.size()-1;
        } else {
            // 题目说了肉不会放到蛇身上，减少了可能的操作
            //body.push_back({tx, ty});
            
            //if (body.back().first == tx && body.back().second == ty) { // 又大意啦，咬尾巴不是咬脖子
            if (body.front().first == tx && body.front().second == ty) {
                // 不会咬到自己的尾巴，去掉尾巴就好
                body.push_back({tx, ty});
                body.pop_front();
                return body.size()-1;
            } else {
                // 检查是否触碰到了自己()
                if (memo.count(pos))
                    return -1;
                body.push_back({tx, ty});
                memo.insert(pos);
                auto [ox, oy] = body.front();
                body.pop_front();
                memo.erase(ox*col + oy);
                return body.size()-1;
            }
        }
    }
};

/**
 * Your SnakeGame object will be instantiated and called as such:
 * SnakeGame* obj = new SnakeGame(width, height, food);
 * int param_1 = obj->move(direction);
 */

int main(int argc, const char * argv[]) {
    vector<int> rtn;
    vector<vector<int>> food;
    
    int m, n;
    SnakeGame gua3(m=3,n=3,food={{2,0}, {0,0}, {0,2}, {2,2}});
    cout << "expect value = 0, actual value = " << gua3.move("D") << endl;
    cout << "expect value = 1, actual value = " << gua3.move("D") << endl;
    cout << "expect value = 1, actual value = " << gua3.move("R") << endl;
    cout << "expect value = 1, actual value = " << gua3.move("U") << endl;
    cout << "expect value = 1, actual value = " << gua3.move("U") << endl;
    cout << "expect value = 2, actual value = " << gua3.move("L") << endl;
    cout << "expect value = 2, actual value = " << gua3.move("D") << endl;
    cout << "expect value = 2, actual value = " << gua3.move("R") << endl;
    cout << "expect value = 2, actual value = " << gua3.move("R") << endl;
    cout << "expect value = 3, actual value = " << gua3.move("U") << endl;
    cout << "expect value = 3, actual value = " << gua3.move("L") << endl;
    cout << "expect value = 3, actual value = " << gua3.move("D") << endl;
    cout << "gua3 finish" << endl;
    
    SnakeGame gua2(m=2,n=2,food={{0,1}});
    cout << "expect value = 1, actual value = " << gua2.move("R") << endl;
    cout << "expect value = 1, actual value = " << gua2.move("D") << endl;
    cout << "gua2 finish" << endl;

    SnakeGame gua(m=3,n=2,food={{1,2},{0,1}});
    cout << "expect value = 0, actual value = " << gua.move("R") << endl;
    cout << "expect value = 0, actual value = " << gua.move("D") << endl;
    cout << "expect value = 1, actual value = " << gua.move("R") << endl;
    cout << "expect value = 1, actual value = " << gua.move("U") << endl;
    cout << "expect value = 2, actual value = " << gua.move("L") << endl;
    cout << "expect value = -1, actual value = " << gua.move("U")<< endl;
    return 0;
}

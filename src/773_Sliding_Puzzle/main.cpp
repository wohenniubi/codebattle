
#include <iostream>
#include <unordered_set>
#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    //Runtime: 8 ms, faster than 92.70%
    //Memory Usage: 8.4 MB, less than 83.16%
    int slidingPuzzle(vector<vector<int>>& board) {
        // 参考网上做法BFS
        
        // 首先存储二维数组的邻居index，便于映射到一维数组之后查询邻居
        // A    B   C   0   1   2
        // D    E   F   3   4   5
        // A的邻居index是1,3
        // B的邻居index是0.2.4
        // ...
        vector<vector<int>> adjs{{1,3},{0,2,4},{1,5},{0,4},{1,3,5},{2,4}};
        
        unordered_set<string> visited;//
        string root;
        int posZ = -1;
        for (int i = 0; i < board.size(); ++i) {
            for (int j = 0; j < board[0].size(); ++j) {
                if (board[i][j] == 0)
                    posZ = 3*i+j;
                root.push_back(board[i][j]+'0');
            }
        }
        root.push_back(posZ+'0');
        queue<string> st{{root}};// 存储需要处理的下一次动作，记得要使用{{}}对queue进行初始化
        
        int rtn = 0;
        while (st.size()) {
            rtn++;// 大意了，忘记增加rtn
            int size = st.size();
            for (int i = 0; i < size; ++i) {
                string tmp = st.front();
                st.pop();
                
                visited.insert(tmp);//应该在这里加入访问
                int posZ = tmp.back()-'0';
                // tmp.pop_back();
                
                //if (tmp == "1234500") 大意了啊大意了！
                if (tmp == "1234505")
                    return rtn-1;
                    
                // 寻找它的邻居
                for (int j = 0; j < adjs[posZ].size(); ++j) {
                    int posNz = adjs[posZ][j];
                    swap(tmp[posNz], tmp[posZ]);
                    tmp.back() = '0'+posNz;
                    
                    // 没有访问过时才存入visited
                    if (!visited.count(tmp)) {
                        // visited.insert(tmp); 大意了不应该在这里加入visited
                        // tmp.push_back('0'+posNz);
                        st.push(tmp);
                    }
                    // 别忘了交换回来
                    swap(tmp[posNz], tmp[posZ]);
                    tmp.back() = '0'+posZ;
                }
            }
        }
        // 跳出while说明不能到达目标
        return -1;
    }
};

int main(int argc, const char * argv[]) {
    Solution gua;
    int rtn;
    vector<vector<int>> board;
    rtn = gua.slidingPuzzle(board={{1,2,3},{4,0,5}});
    cout << "expect result = 1, actual result = " << rtn << endl;

    rtn = gua.slidingPuzzle(board={{1,2,3},{5,4,0}});
    cout << "expect result = -1, actual result = " << rtn << endl;

    rtn = gua.slidingPuzzle(board={{4,1,2},{5,0,3}});
    cout << "expect result = 5, actual result = " << rtn << endl;

    rtn = gua.slidingPuzzle(board={{3,2,4},{1,5,0}});
    cout << "expect result = 14, actual result = " << rtn << endl;

    return 0;
}


#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    #define UP 0
    #define DW 1
    #define LF 2
    #define RT 3
    
    //Runtime: 60 ms, faster than 67.86%
    //Memory Usage: 16.4 MB, less than 75.00%
    int minArea(vector<vector<char>>& image, int x, int y) {
        // 看答案吧，由于只要一个矩形，所以仅仅需要上下左右的边框就可以获
        vector<int> dirs{INT_MAX, INT_MIN, INT_MAX, INT_MIN};
        
        for (int i = 0; i < image.size(); ++i) {
            for (int j = 0; j < image[i].size(); ++j) {
                if (image[i][j] == '1') {
                    dirs[UP] = min(dirs[UP], i);
                    dirs[DW] = max(dirs[DW], i);
                    
                    dirs[LF] = min(dirs[LF], j);
                    dirs[RT] = max(dirs[RT], j);
                }
            }
        }
        
        // 现在计算矩形的面积
        int weight = dirs[RT] - dirs[LF] + 1;
        int height = dirs[DW] - dirs[UP] + 1;
        return weight*height;
    }
};

int main(int argc, const char * argv[]) {
    Solution gua;
    vector<vector<char>> image;
    int rtn, x, y;
    rtn = gua.minArea(image={{'0','0','1','0'},{'0','1','1','0'},{'0','1','0','0'}}, x, y);
    cout << "expect value = 6, actual value = " << rtn << endl;
    return 0;
}

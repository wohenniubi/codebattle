
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    static bool myCmp(vector<int> &A, vector<int> &B) {
        // 以右边界递增排序，右边界相同时以左边界升序排序;
        if (A[1] != B[1])
            return A[1] < B[1];
        return A[0] < B[0];
    }
    
    //Runtime: 136 ms, faster than 76.32%
    //Memory Usage: 34.7 MB, less than 99.25%
    int findMinArrowShots(vector<vector<int>>& points) {
        int size = points.size();
        if (0 == size) return 0;
        
        // interval问题，特殊的俄罗斯套娃问题，排序之后可以以greedy方式O(n)解决
        sort(begin(points), end(points), myCmp);
        
        // 现在开始greedy
        int cnt = 0;// 记录重复的、可以被去掉的interval
        for (int prev = 0, i = 1; i < size; ++i) {
            //   |--- prev ---|
            //      |---- i ----|
            // |------- i --------|
            //                  |-- i --|
        
            if (points[prev][1] >= points[i][0]) {
                cnt++;
            } else {
                prev=i;
            }
        }
        return size-cnt;
    }
};

int main(int argc, const char * argv[]) {
    Solution gua;
    int rtn;
    vector<vector<int>> points;
    rtn = gua.findMinArrowShots(points = {{10,16},{2,8},{1,6},{7,12}});
    cout << "expect value = 2, actual value = " << rtn << endl;

    rtn = gua.findMinArrowShots(points = {{1,2},{3,4},{5,6},{7,8}});
    cout << "expect value = 4, actual value = " << rtn << endl;

    rtn = gua.findMinArrowShots(points = {{1,2}});
    cout << "expect value = 1, actual value = " << rtn << endl;
    return 0;
}

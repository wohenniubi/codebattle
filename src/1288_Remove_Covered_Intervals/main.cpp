
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    static bool myCmp(vector<int> &A, vector<int> &B) {
        if (A[0] == B[0])
            return A[1] > B[1];
        //在左边界相同时，按照右边界降序排列，保证排序后只会出现下面的情况
        // A.begin() --------- A.end()
        // B.begin() --- B.end()
        
        return A[0] < B[0];// 按照start左边界进行排序
    }
    
    //Runtime: 20 ms, faster than 88.85%
    //Memory Usage: 11.3 MB, less than 50.56%
    int removeCoveredIntervals(vector<vector<int>>& intervals) {
        int size = intervals.size();
        if (size < 2) return 0;
        int cnt = 0;
        
        sort(begin(intervals), end(intervals), myCmp);
        int prev = 0;
        for (int i = 1; i < size; ++i) {
            if (intervals[prev][0] == intervals[i][0]) {
                // 因为不会有重复的interval，所以此刻必定是覆盖的情况
                // A.begin() --------- A.end()
                // B.begin() --- B.end()
                cnt++;
            } else {
                assert(intervals[prev][0] < intervals[i][0]);
                // 此时只会有3种情况;
                // A.begin() --------- A.end()
                //     B.begin() --- B.end()

                // A.begin() --------- A.end()
                //                               B.begin() --- B.end()

                // A.begin() --------- A.end()
                //            B.begin() --- B.end()

                // 对于第一种是覆盖
                //if (intervals[prev][1] <= intervals[i][1]) { 大意了啊大意了啊！！
                if (intervals[prev][1] >= intervals[i][1]) {
                    cnt++;
                } else { // 剩下两种情况都是继续执行
                    prev = i;
                }
            }
        }
        
        return size - cnt;
    }
};

int main(int argc, const char * argv[]) {
    Solution gua;
    vector<vector<int>> intervals;
    int rtn;
    rtn = gua.removeCoveredIntervals(intervals={{1,4},{3,6},{2,8}});
    cout << "expect value = 2, actual value = " << rtn << endl;
    
    rtn = gua.removeCoveredIntervals(intervals={{0,10},{5,12}});
    cout << "expect value = 2, actual value = " << rtn << endl;

    rtn = gua.removeCoveredIntervals(intervals={{1,4},{2,3}});
    cout << "expect value = 1, actual value = " << rtn << endl;

    rtn = gua.removeCoveredIntervals(intervals={{3,10},{4,10},{5,11}});
    cout << "expect value = 2, actual value = " << rtn << endl;

    rtn = gua.removeCoveredIntervals(intervals={{1,2},{1,4},{3,4}});
    cout << "expect value = 1, actual value = " << rtn << endl;

    rtn = gua.removeCoveredIntervals(intervals={{34335,39239},{15875,91969},{29673,66453},{53548,69161},{40618,93111}});
    cout << "expect value = 2, actual value = " << rtn << endl;

    return 0;
}

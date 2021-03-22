
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    // in-place mergeSort时处理subarray1和subarray2，将后者merge到前者
    // 当出现前者[i]大于后者[j]时，保留j这个位置的值，同时将[i,j)的值整理右移1位，
    // 再把保存的j位置的值存入[i]，然后再更新i和j，有点复杂哇；那就还是用pivotSort吧
    void pivotSort(vector<vector<int>>& intervals, int bgn, int end) {
        if (bgn >= end) return;
        
        int lhs = bgn, pos = end-1;
        for (int i = bgn; i < pos; ++i) {
            if (intervals[i][1] < intervals[pos][1]
               || (intervals[i][1] == intervals[pos][1]
               && intervals[i][0] < intervals[pos][0])) {
                swap(intervals[i], intervals[lhs]);
                lhs++;
            }
        }
        swap(intervals[lhs], intervals[pos]);
        //int mid = bgn + (end-bgn)/2; 这是mergeSort的参数
        int mid = lhs;
        
        pivotSort(intervals, bgn, mid);
        pivotSort(intervals, mid+1, end);// 一定要+1，否则可能造成死循环
        return;
    }
    
    static bool myCmp(vector<int> &A, vector<int> &B) {
        if (A[1] == B[1])
            return A[0] < B[0];
        return A[1] < B[1];
    }
    
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        if (intervals.empty()) return 0;
        
        // 复习一下二分排序mergeSort
        //Runtime: 208 ms, faster than 5.41%
        //Memory Usage: 10.3 MB, less than 69.76%
        //pivotSort(intervals, 0, intervals.size());
        
        //Runtime: 12 ms, faster than 96.24%
        //Memory Usage: 10.2 MB, less than 76.25%
        sort(begin(intervals), end(intervals), myCmp);
        
        int rtn = 0;
        for (int prev=0, i = 1; i < intervals.size(); ++i) {
            if (intervals[prev][1] > intervals[i][0]) {
                rtn++;
            } else {
                prev = i;// 怎么这么大意，忘记更新prev了
            }
        }
        return rtn;
    }
};

int main(int argc, const char * argv[]) {
    Solution gua;
    int rtn;
    vector<vector<int>> intervals;
    
    rtn = gua.eraseOverlapIntervals(intervals = {{0,2}, {1,3}, {2,4}, {3,5}, {4,6}});
    cout << "expect result = 2, actual result = " << rtn << endl;
    
    rtn = gua.eraseOverlapIntervals(intervals = {{1,2}, {2,3}, {3,4}, {1,3}});
    cout << "expect result = 1, actual result = " << rtn << endl;
    
    rtn = gua.eraseOverlapIntervals(intervals = {{1,2}, {1,2}, {1,2}});
    cout << "expect result = 2, actual result = " << rtn << endl;

    rtn = gua.eraseOverlapIntervals(intervals = {{1,2}, {2,3}});
    cout << "expect result = 0, actual result = " << rtn << endl;
    return 0;
}

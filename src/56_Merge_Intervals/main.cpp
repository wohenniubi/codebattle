
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    // 因为要merge成为更大的interval，我觉得还是按照左边界升序排列，好一点
    static bool myCmp(vector<int> &A, vector<int> &B) {
        if (A[0] == B[0]) {
            // 对于左边界相同时，要不要特殊处理右边界，保证sort之后只会出现下面的情况，这样就可以一直沿用A来进行操作，代码简单
            // A.begin() --------- A.end()
            // B.begin() ---- B.end()
            return A[1] > B[1];
        }
        return A[0] < B[0];
    }
    
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        int size = intervals.size();
        if (size < 2) return intervals;// 此刻不用merge了
        
        // interval问题，先sort，然后再操作就好了
        sort(begin(intervals), end(intervals), myCmp);
        
        vector<vector<int>> rtn = {intervals[0]}; // 稍微注意的地方在于边界问题，最后一个interval怎么入樽
        for (int i = 1; i < size; ++i) {
            if (rtn.back()[0] == intervals[i][0]) {
                // 此时必定是merge，因为右边界是按照降序排列的;
                // 就不操作了
                ;
            } else {
                assert(rtn.back()[0] < intervals[i][0]);
                // 此时有3种情况
                // A.begin() --------- A.end()
                //    B.begin() ---- B.end()
                // A.begin() --------- A.end()
                //          B.begin() ---- B.end()
                // A.begin() --------- A.end()
                //                               B.begin() ---- B.end()
                if (rtn.back()[1] < intervals[i][0]) {
                    // merge不上啦，有断层啦
                    rtn.push_back(intervals[i]);
                } else {
                    // 扩充一下区间的右边界
                    rtn.back()[1] = max(rtn.back()[1], intervals[i][1]);
                }
            }
        }
        
        return rtn;
    }
};

ostream & operator<< (ostream &os, vector<vector<int>> &rtn) {
  os << "[";
  for (auto & inter : rtn) {
    os << "[" << inter[0] << "," << inter[1] << "], ";
  }
  os << "]";
  return os;
}

int main(int argc, const char * argv[]) {
    Solution gua;
    vector<vector<int>> intervals, rtn;
    rtn = gua.merge(intervals={{1,3},{2,6},{8,10},{15,18}});
    cout << "expect value = [[1,6],[8,10],[15,18]], actual value = " << rtn << endl;
    
    rtn = gua.merge(intervals={{1,4},{4,5}});
    cout << "expect value = [[1,5]], actual value = " << rtn << endl;

    return 0;
}



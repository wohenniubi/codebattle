
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

/*  Definition for an Interval.*/
class Interval {
public:
    int start;
    int end;

    Interval() {}

    Interval(int _start, int _end) {
        start = _start;
        end = _end;
    }
};

class Solution {
public:
    static bool myCmp(Interval &A, Interval &B) {
        if (A.start == B.start) {
            return A.end > B.end;
        }
        return A.start < B.start;
    }
    
    //Runtime: 32 ms, faster than 77.32%
    //Memory Usage: 10.4 MB, less than 80.54%
    vector<Interval> employeeFreeTime(vector<vector<Interval>> schedule) {
        // 基本思路不变，还是以起始边界升序排列，然后以右边界降序排列
        // 巧妙的是需要先将schedule排平，变成一个vector
        vector<Interval> flat;
        for (int i = 0; i < schedule.size(); ++i) {
            for (int j = 0; j < schedule[i].size(); ++j) {
                flat.push_back(schedule[i][j]);
            }
        }
        
        sort(flat.begin(), flat.end(), myCmp);
        int prev = 0; // 然后将interval进行merge，产生的gap就是我们的所需
        vector<Interval> rtn;
        for (int i = 1; i < flat.size(); ++i) {
            if (flat[prev].start == flat[i].start) {
                // 此时两者的end只有以下几种情况; 都用prev来merge，此时prev不变
                // flat[prev].start ---- flat[prev].end
                // flat[i].start --- flat[i].end
                // flat[i].start ---------- flat[i].end
                prev = prev;
            } else {
                assert(flat[prev].start < flat[i].start);
                // 此时两者的end只有以下几种情况; 都用prev来merge，此时prev不变
                // flat[prev].start ------- flat[prev].end
                //    flat[i].start --- flat[i].end
                //    flat[i].start ---------- flat[i].end
                //    flat[i].start ---------------- flat[i].end
                //                                       flat[i].start ---------- flat[i].end
                if (flat[prev].end < flat[i].start) {
                    // 仅有此时才会出现gap
                    rtn.push_back(Interval(flat[prev].end, flat[i].start));
                    prev = i;
                } else {
                    // 此时让prev的右边界最长
                    flat[prev].end = max(flat[prev].end, flat[i].end);
                }
            }
        }
        
        return rtn;
    }
};

ostream & operator<<(ostream &os, vector<Interval> &rtn) {
    os << "[";
    for (auto & item : rtn) {
        os << "[" << item.start << "," << item.end << "], ";
    }
    
    os << "]";
    return os;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    Solution gua;
    vector<Interval> rtn;
    vector<vector<Interval>> schedule;
    
    rtn = gua.employeeFreeTime(schedule = {{{1,2},{5,6}}, {{1,3}}, {{4,10}}});
    cout << "expect value = [[3,4]], actual value = " << rtn << endl;

    rtn = gua.employeeFreeTime(schedule = {{{1,3},{6,7}},{{2,4}},{{2,5},{9,12}}});
    cout << "expect value = [[5,6], [7,9]], actual value = " << rtn << endl;
    return 0;
}

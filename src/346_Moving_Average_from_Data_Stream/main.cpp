
#include <iostream>
#include <vector>

using namespace std;

//Runtime: 44 ms, faster than 51.43%
//Memory Usage: 14 MB, less than 70.08%
class MovingAverage {
public:
    /** Initialize your data structure here. */
    MovingAverage(int size) {
        winSize = size;
        gsum = 0;
    }

    void popVal(void) {
        gsum -= helper.front();
        helper.erase(helper.begin());
    }
    
    void addVal(int val) {
        helper.push_back(val);
        gsum += val;
        while (helper.size() > winSize) {
            popVal();
        }
    }
    
    double next(int val) {
        addVal(val);
        //return ((double)gsum)/((double)helper.size());
        return gsum/helper.size();
    }

private:
    int winSize;
    double gsum;// 很巧妙的做法，把gsum定义为double类型，则不用强制转换了
    vector<int> helper;
};

int main(int argc, const char * argv[]) {
    MovingAverage sol(3);
    double rtn;
    rtn = sol.next(1);
    cout << "expect value = 1, actual value = " << rtn << endl;
    
    rtn = sol.next(10);
    cout << "expect value = 5.5, actual value = " << rtn << endl;
    
    rtn = sol.next(3);
    cout << "expect value = 4.66667, actual value = " << rtn << endl;

    rtn = sol.next(5);
    cout << "expect value = 6, actual value = " << rtn << endl;
    return 0;
}

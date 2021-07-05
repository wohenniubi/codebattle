
#include <iostream>
#include <map>
#include <set>

using namespace std;

typedef pair<int,int> MYTYPE;
struct MyCmp {
    // bool operator()(MYTYPE& A, MYTYPE& B) { // 为何如此超级大意？？要用const呀
    bool operator()(const MYTYPE& A, const MYTYPE& B) const {
        if (A.first == B.first) {
            return A.second < B.second;
        }
        return A.first < B.first;
    }
};

class MyCalendarTwo {
public:
    map<int, int> memo; // key是事件的起始时间，val是事件发生的次数，总体结构相当于是前缀和数组
    
    //Runtime: 192 ms, faster than 51.20%
    //Memory Usage: 38.9 MB, less than 35.42%
    MyCalendarTwo () {
        memo.clear();
    }
    
    bool book(int start, int end) {
        ++memo[start];// 这里在起始时间checkin了一个事件
        --memo[end]; // 这里在结束时间check out注销了一个事件
        
        int cnt = 0;
        for (auto & [key, val] : memo) {
            cnt += val;
            if (cnt >= 3) {
                --memo[start];
                ++memo[end];
                return false;
            }
            if (key >= end) break;// 后续事件都在当前事件结束之后，因此不会受到影响，提前返回吧
        }
        return true;
    }
};

class MyCalendarTwoNotWork {
public:
    // 感觉还是与729类似，以开始为key，以end为value，不过由于key可能重复，所以需要用multimap
    // 然后对于multimap<int,int>来讲，如果比较函数要考虑到val，那么这样的multimap就没有意义，
    // 因此使用multiset + pair的方式来实现 —— 但是实际情况是，729的方法不工作啊
    // multimap<int, int> memo;
    multiset<MYTYPE, MyCmp> memo;
    
    MyCalendarTwoNotWork() {
        memo.clear();
    }
    
    bool book(int start, int end) {
        //auto lhs = memo.lower_bound(start);
        //auto rhs = memo.upper_bound(end);
        auto lhs = memo.lower_bound({start, INT_MIN});
        auto rhs = memo.upper_bound({end, INT_MIN});
        
        // 之所以能这么做，是因为如果按照MyCmp的比较函数，lower_bound得到的第一个间隔就是
        // 最可能产生交叠的，同时第一个间隔与upper_bound的间隔可以判断出这部分有多少重叠
        if (distance(lhs, rhs) >= 2 && (*lhs).first < end) {
            return false;
        }
        memo.insert({start, end});
        return true;
    }
};

/**
 * Your MyCalendarTwoNotWork object will be instantiated and called as such:
 * MyCalendarTwoNotWork* obj = new MyCalendarTwoNotWork();
 * bool param_1 = obj->book(start,end);
 */

int main(int argc, const char * argv[]) {
    // insert code here...
    cout << "\nTest 1" << endl;
    MyCalendarTwo gua;
    cout << "expect value = 1, actual value = " << gua.book(24,40) << endl;
    cout << "expect value = 1, actual value = " << gua.book(43,50) << endl;
    cout << "expect value = 1, actual value = " << gua.book(27,43) << endl;
    cout << "expect value = 1, actual value = " << gua.book(5,21) << endl;
    cout << "expect value = 0, actual value = " << gua.book(30,40) << endl;
    
    cout << "\nTest 2" << endl;
    MyCalendarTwo gua2;
    cout << "expect value = 1, actual value = " << gua2.book(10,20) << endl;
    cout << "expect value = 1, actual value = " << gua2.book(50,60) << endl;
    cout << "expect value = 1, actual value = " << gua2.book(10,40) << endl;
    cout << "expect value = 0, actual value = " << gua2.book(5,15) << endl;
    cout << "expect value = 1, actual value = " << gua2.book(5,10) << endl;
    cout << "expect value = 1, actual value = " << gua2.book(25,55) << endl;
    
    return 0;
}

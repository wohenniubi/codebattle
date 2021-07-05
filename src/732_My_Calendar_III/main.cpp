
#include <iostream>
#include <map>

using namespace std;

class MyCalendarThree {
public:
    map<int, int> memo;
    int max_cnt;
    //Runtime: 68 ms, faster than 91.67%
    //Memory Usage: 26.5 MB, less than 28.49%
    MyCalendarThree() {
        memo.clear();
        memo[INT_MIN] = 0;
        memo[INT_MAX] = 0;// 还需要加入两个辅助点，巧妙的解决初次加入数据（冷启动）的问题
        max_cnt = 0;// 还要记录一个全局变量，如果没有影响到已有间隔的话，那就用上一次的值来返回
    }
    
    // 这种方法memo的含义是:以某个时刻作为起点的事件个数，每次booking时不需要从头到尾遍历，但是需要自己维护每个时刻的事件数
    // 这种做法会将一个事件拆分为不同起始时刻的两个事件
    // 时间复杂度O(n*m)，其中m是可能出现重复的那些时刻，其上限是n，因此效率比book1要快一些——做法有点像715 Range Module
    int book(int start, int end) {
        auto lhs = prev(memo.upper_bound(start));
        auto rhs = memo.lower_bound(end);// 很厉害，这次是对start进行upper_bound，对end进行lower_bound
        
        // 后记：只要进入下面的for loop，memo[start]和memo[end]一定会更新，不要担心被漏掉
        // 因为lhs和rhs代表了小于等于start，和以end为结束时刻的区间，是左闭右开的——prev非常巧妙，要再向左延伸一位
        for (auto cur = lhs, next = lhs; cur != rhs; cur = next) {
            ++next;
            // 还必须把memo[end]的更新放在前面，因为下面的分支可能修改cur->second
            // if (next->first >= end) { //仅在rhs-1那个间隔触发一次，还要注意不包括等于
            if (next->first > end) {
                // 说明下一个时刻是在end之后，那么end与这个时刻之间不会有事件，
                // 因此memo[end]的值可以继承于next->second;  next->first必然大于start
                // 例如：[INT_MIN] = 0        [INT_MAX] = 0
                //                   [10, 20]
                //       lhs: cur               rhs
                // memo[end] = next->second; // 别大意，沿用的是当前的个数，next是下一个了，不正确
                memo[end] = cur->second;
                // 由于memo[end]是沿用cur->second，因此要让起始时刻next->first完全超过end才能更新memo[end]
            }
            
            // 接下来是更新start时刻的事件个数了，由于cur和next是相邻的两个时刻
            // 当且仅当start处于这两个时刻之间时，会继承cur时刻的事件个数并且加1 (cur时刻比start先)
            if (cur->first <= start && next->first > start) {
                memo[start] = cur->second + 1;
                max_cnt = max(max_cnt, memo[start]);
            } else {
                // 否则的话，即cur->first > start || next->first <= start
                // 前者意味着cur这个时刻在start事件发生之后，那么cur时刻的事件个数要加1;
                // 由于rhs是end的lower_bound，因此只要还在这个for循环里面，start时刻开始的事件就还没有结束
                max_cnt = max(max_cnt, ++(cur->second));
            }
        }
        return max_cnt;// 如果没有找到lhs和rhs的区间，说明没有影响到已有事件，那么最大值不变
    }
    
};

class MyCalendarThree1 {
public:
    map<int, int> memo;
    MyCalendarThree1() {
        memo.clear();
    }

    //Runtime: 96 ms, faster than 70.03%
    //Memory Usage: 26.4 MB, less than 28.88%
    //这种方法memo的含义是某个时刻事件变化的次数，然后每次booking时需要从头到尾遍历一遍，时间复杂度O(n^2)
    int book(int start, int end) {
        ++memo[start];
        --memo[end];
        
        int cnt = 0;
        int rtn = 0;
        for (auto & [key, val] : memo) {
            cnt += val;
            rtn = max(cnt, rtn);
        }
        return rtn;
    }
};

int main(int argc, const char * argv[]) {
    // insert code here...
    MyCalendarThree gua3;
    cout << "\nTest3" << endl;
    cout << "expect value = 1, actual value = " << gua3.book(28, 46) << endl;
    cout << "expect value = 1, actual value = " << gua3.book(9, 21) << endl;
    cout << "expect value = 2, actual value = " << gua3.book(21, 39) << endl;
    cout << "expect value = 3, actual value = " << gua3.book(37, 48) << endl;
    cout << "expect value = 4, actual value = " << gua3.book(38, 50) << endl;
    cout << "expect value = 5, actual value = " << gua3.book(22, 39) << endl;
    cout << "expect value = 5, actual value = " << gua3.book(45, 50) << endl;
    cout << "expect value = 5, actual value = " << gua3.book(1, 12) << endl;
    cout << "expect value = 5, actual value = " << gua3.book(40, 50) << endl;

    MyCalendarThree gua2;
    cout << "\nTest2" << endl;
    cout << "expect value = 1, actual value = " << gua2.book(47, 50) << endl;
    cout << "expect value = 1, actual value = " << gua2.book(1, 10) << endl;
    cout << "expect value = 1, actual value = " << gua2.book(27, 36) << endl;
    cout << "expect value = 1, actual value = " << gua2.book(40, 47) << endl;
    cout << "expect value = 1, actual value = " << gua2.book(20, 27) << endl;
    cout << "expect value = 2, actual value = " << gua2.book(15, 23) << endl;
    cout << "expect value = 2, actual value = " << gua2.book(10, 18) << endl;
    cout << "expect value = 2, actual value = " << gua2.book(27, 36) << endl;
    cout << "expect value = 3, actual value = " << gua2.book(17, 25) << endl;
    cout << "expect value = 3, actual value = " << gua2.book(8, 17) << endl;
    cout << "expect value = 3, actual value = " << gua2.book(24, 33) << endl;

    MyCalendarThree gua;
    cout << "\nTest1" << endl;
    cout << "expect value = 1, actual value = " << gua.book(10, 20) << endl;
    cout << "expect value = 1, actual value = " << gua.book(50, 60) << endl;
    cout << "expect value = 2, actual value = " << gua.book(10, 40) << endl;
    cout << "expect value = 3, actual value = " << gua.book(5, 15) << endl;
    cout << "expect value = 3, actual value = " << gua.book(5, 10) << endl;
    cout << "expect value = 3, actual value = " << gua.book(25, 55) << endl;

    return 0;
}

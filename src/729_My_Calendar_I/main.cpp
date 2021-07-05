
#include <iostream>
#include <map>

using namespace std;

class MyCalendar {
    // 觉得和那道715很像，由于能够加入的calendar本身是没有重叠的，因此一个map就可以解决
    map<int,int> memo;// key是起点，val是结束时间
    
public:
    MyCalendar() {
        memo.clear();
    }
    
    //Runtime: 84 ms, faster than 81.83%
    //Memory Usage: 39.3 MB, less than 12.05%
    bool book(int start, int end) {
        auto lhs = memo.lower_bound(start);
        auto rhs = memo.upper_bound(end);//找到的是完全大于end的间隔
        
        // 找到是否出现overlap的间隔，要往前找一个间隔
        if (lhs != begin(memo)) {
            // 前一个间隔的结束位置和start一样，不作为重叠
            if ((--lhs)->second <= start) {
                ++lhs;// 恢复lhs为原始的lhs
            }
        }
        // return (lhs == rhs);// 如果两者相同，说明没有重叠
        
        //if (lhs != rhs) return false;// 别大意啊，还要把这个值加入到memo里面
        // 本题与715的不同之处在于，后者可以merge边界重合的间隔，本题不行；故要剔除lhs->first == end的情况
        if (lhs != rhs && lhs->first < end) return false;
        memo[start] = end;
        return true;
    }
};

/**
 * Your MyCalendar object will be instantiated and called as such:
 * MyCalendar* obj = new MyCalendar();
 * bool param_1 = obj->book(start,end);
 */

int main(int argc, const char * argv[]) {
    // insert code here...
    cout << "\nTest 1" << endl;
    MyCalendar gua2;
    cout << "expect value = 1, actual value = " << gua2.book(20,29) << endl;
    cout << "expect value = 0, actual value = " << gua2.book(13,22) << endl;
    cout << "expect value = 1, actual value = " << gua2.book(44,50) << endl;
    cout << "expect value = 1, actual value = " << gua2.book(1,7) << endl;
    cout << "expect value = 0, actual value = " << gua2.book(2,10) << endl;
    cout << "expect value = 1, actual value = " << gua2.book(14,20) << endl;

    cout << "\nTest 2" << endl;
    MyCalendar gua;
    cout << "expect value = 1, actual value = " << gua.book(47,50) << endl;
    cout << "expect value = 1, actual value = " << gua.book(33,41) << endl;
    cout << "expect value = 0, actual value = " << gua.book(39,45) << endl;
    cout << "expect value = 0, actual value = " << gua.book(33,42) << endl;
    cout << "expect value = 1, actual value = " << gua.book(25,32) << endl;
    cout << "expect value = 0, actual value = " << gua.book(26,35) << endl;
    cout << "expect value = 1, actual value = " << gua.book(19,25) << endl;
    cout << "expect value = 1, actual value = " << gua.book(3,8) << endl;
    cout << "expect value = 1, actual value = " << gua.book(8,13) << endl;
    cout << "expect value = 0, actual value = " << gua.book(18,27) << endl;
    
    return 0;
}

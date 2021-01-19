#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class MedianFinder {
public:
    //Runtime: 128 ms, faster than 93.35%
    //Memory Usage: 46.7 MB, less than 97.41%
    /** initialize your data structure here. */
    MedianFinder() {
        // 对于每次传入一个未知的数，如果每次都排序，那么复杂度会变成n*O(nlogn)
        // 本题的难点在于需要尽快找到中间的两个值，其他的数只要分别在较小的组和较大的组就行了，详细的大小关系不用管
        // 注意，仅仅一个heap是搞不定的，因为help的规则只要父节点比子节点小就可以了，故无法保证节点是ordered的情况
    }

    void addNum(int num) {
        // 难点是加入一个数时要维护lhs和rhs
        if (lhs.empty()) {
            lhs.push(num);
            return; // 固定lhs的规模大于rhs
        }

        // 不管怎样都要先加入lhs洗礼一下
        lhs.push(num);
        // 把lhs最大的取出来，再放到rhs里面去洗礼一下
        rhs.push(lhs.top());
        // 好啦这样的话，左右分组继续满足左分组<=右分组的情况

        // 开始维护左右分组的数据规模，因为左右分支都增加了1，所以大小关系与先前并不变
        // e.g. [1,2] [50, 60]  + 100 -> [1,2,100] [50, 60, 100]，此时去掉rhs里面的top，将该top放入lhs
        // e.g. [1,15] [20]  + 10 -> [1,10,15] [15, 20]，此时去掉lhs里面的top
        // e.g. [1,15] [20]  + 100 -> [1,15,100] [20, 100]，此时去掉lhs里面的top
        if (lhs.size() == rhs.size()) {
            // 要把num放到lhs，保证比rhs多
            // lhs.top() = rhs.top();貌似还不允许这么操作
            lhs.push(rhs.top());
            lhs.pop();
            rhs.pop();
        } else {
            // 要把num放到rhs，去掉左边最大的那个值，那个值必定已经进入了rhs，
            lhs.pop();
        }
        return;
    }

    double findMedian() {
        double rtn = -1.0;
        if (lhs.empty()) return rtn;//因为默认lhs的数量比rhs多

        // 如果lhs和rhs的数据规模相同，那么就是取平均
        if (lhs.size() == rhs.size()) {
            rtn = lhs.top() + (rhs.top() - lhs.top())/2.0;
        } else {
            rtn = lhs.top();
        }
        return rtn;
    }

    priority_queue<int> lhs;//数据规模为n/2, 所有数据<= rhs
    priority_queue<int, vector<int>, greater<int>> rhs;//数据规模n/2,所有数据>= lhs里的数据
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */

int main() {
  MedianFinder gua;
  vector<int> test;

  test = vector<int>{1,2,-1,3,-1};
  for (int i = 0; i < test.size() ; ++i) {
  //for (auto val : test) {
    if (test[i] >= 0)
      gua.addNum(test[i]);
    else
      cout << "expect value = " << ((i==2)?1.5:2.0) << ", actual value = " << gua.findMedian() << endl;
  }
  
  return 0;
}


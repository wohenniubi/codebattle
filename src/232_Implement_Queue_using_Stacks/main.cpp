
#include <iostream>
#include <stack>

using namespace std;

class MyQueue {
public:
    stack<int> sforPop, sforPush;
    
    //Runtime: 0 ms, faster than 100.00%
    //Memory Usage: 7.1 MB, less than 81.51%
    /** Initialize your data structure here. */
    MyQueue() {
        
    }
    
    /** Push element x to the back of queue. */
    void push(int x) {
        sforPush.push(x);
    }
    
    /** Removes the element from in front of queue and returns that element. */
    int pop() {
        if (empty()) return -1;//如果队列空了，就返回别再调用了
        
        // 和peek有同样的操作，都要让sforPush导出所有数据，所以复用peek代码
        peek();
        // return sforPop.top(); 大意啦，别忘了pop掉这个数据啊。。。
        int rtn = sforPop.top();
        sforPop.pop();
        return rtn;
    }
    
    /** Get the front element. */
    // 最坏时间复杂度是O(n)，不过题目说amortized（均摊）时间复杂度，
    // 那么均摊到每个成员，因为只可能被peek一次，所以凑合还是O(1)吧
    int peek() {
        if (empty()) return -1;//如果队列空了，就返回别再调用了
        
        if (sforPop.size()) return sforPop.top();
        // sforPop空了，需要从sforPush里面导出所有数据，即反序
        while (sforPush.size()) {
            sforPop.push(sforPush.top());
            sforPush.pop();
        }// 跳出循环表明sforPush为空
        return sforPop.top();
    }
    
    /** Returns whether the queue is empty. */
    bool empty() {
        //可能正好位于某个stack为空的情况，所以要两个都为空才行
        return (sforPop.empty() && sforPush.empty());
    }
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */

int main(int argc, const char * argv[]) {
    MyQueue gua;
    gua.push(1);
    gua.push(2);
    cout << "expect value = 1, actual value = " << gua.peek() << endl;
    int rtn = gua.pop();
    cout << "expect value = 1, actual value = " << rtn << endl;

    cout << "expect value = 2, actual value = " << gua.peek() << endl;
    gua.pop();
    cout << "expect value = 1, actual value = " << gua.empty() << endl;

    return 0;
}

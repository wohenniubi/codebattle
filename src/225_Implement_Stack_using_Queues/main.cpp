
#include <iostream>
#include <queue>

using namespace std;

class MyStack {
public:
    //Runtime: 0 ms, faster than 100.00%
    //Memory Usage: 6.8 MB, less than 97.05%
    queue<int> q;
    int topVal;// 记录栈top的val
    
    /** Initialize your data structure here. */
    MyStack() {
        
    }
    
    /** Push element x onto stack. */
    void push(int x) {
        // q.push_back(x);
        q.push(x);
        topVal = x;
    }
    
    /** Removes the element on top of the stack and returns that element. */
    int pop() {
        if (q.empty()) return -1;
        
        // 没有办法，只能FIFO，得循环
        int size = q.size();
        // 循环n-1次，把最后一个数移动到队首
        while (size > 1) {
            // push(q.top());大意了，queue没有top
            push(q.front());
            q.pop();
            --size;// 这里太太太大意了！！！忘记加入--size导致死循环
        }
        // 现在的top就是栈顶元素了
        int rtn = q.front();
        q.pop();
        return rtn;
    }
    
    /** Get the top element. */
    int top() {
        if (q.empty()) return -1;
        
        return topVal;
    }
    
    /** Returns whether the stack is empty. */
    bool empty() {
        return q.empty();
    }
};

/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack* obj = new MyStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * bool param_4 = obj->empty();
 */

int main(int argc, const char * argv[]) {
    MyStack gua;
    int rtn;
    gua.push(1);
    gua.push(2);
    rtn = gua.top();
    cout << "expect value = 2, actual value = " << rtn << endl;
    rtn = gua.pop();
    cout << "expect value = 2, actual value = " << rtn << endl;
    cout << "expect value = 0, actual value = " << gua.empty() << endl;
    
    return 0;
}

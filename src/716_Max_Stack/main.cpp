#include <iostream>
#include <vector>
#include <list>
#include <map>

using namespace std;

// 网上的做法是双栈，一个栈是普通栈，一个栈是顺序栈
//Runtime: 136 ms, faster than 89.51%
//Memory Usage: 36.5 MB, less than 85.37%
class MaxStack {
public:
    /** initialize your data structure here. */
    MaxStack() {
        
    }
    
    void push(int x) {
        norm_st.push_back(x);
        
        //if (max_st.empty() || x >= max_st.front()) {
        //大意啦大意啦，用vector替代stack的话，是比较最后一个元素！！！
        if (max_st.empty() || x >= max_st.back()) {
            max_st.push_back(x);
        }
    }
    
    int pop() {
        int rtn = norm_st.back();
        norm_st.pop_back();
        
        // 需要维护max_st里面的top值
        if (rtn == max_st.back())
            max_st.pop_back();
        
        return rtn;
    }
    
    int top() {
        return norm_st.back();
    }
    
    int peekMax() {
        return max_st.back();
    }
    
    int popMax() {
        vector<int> tmp_st;
        int rtn = max_st.back();
        max_st.pop_back();
        
        // 从norm_st里面倒出来那个最大的值，只能while
        while (norm_st.size()) {
            if (norm_st.back() < rtn) {
                tmp_st.push_back(norm_st.back());
                norm_st.pop_back();
            } else {
                norm_st.pop_back();
                break;// 找到了一个最大的值，去掉这个值，跳出while
            }
        }
        
        // 注意需要把tmp_st里面的值重新放回到norm_st和max_st里面
        while (tmp_st.size()) {
            push(tmp_st.back());
            tmp_st.pop_back();
        }
        return rtn;
    }
private:
    vector<int> norm_st, max_st;
};

// 我想的是双向链表+哈希（红黑）表的形式，实现起来麻烦一点；复习一下list的用法吧
//Runtime: 156 ms, faster than 59.30%
//Memory Usage: 38.6 MB, less than 72.02%
class MaxStack1{
public:
    MaxStack1() {}
    
    void push(int x) {
        // 顺序增加到链表头，这样的好处是所需的iter就是表头
        v.insert(v.begin(), x);
        
        // 维护哈希map
        helper[x].push_back(v.begin());
    }

    int pop() {
        int rtn = v.front();
        v.erase(v.begin());

        // 维护哈希表，新增的iter都是在最后，所以从后往前pop是安全的
        helper[rtn].pop_back();
        if (helper[rtn].empty()) helper.erase(rtn);
        
        return rtn;
    }

    int top() {
        return v.front();
    }

    int peekMax() {
        // 因为是红黑树，默认排序右边最大
        return helper.rbegin()->first;
    }

    int popMax() {
        // 获得红黑树里面存的iter
        int rtn = helper.rbegin()->first;
        
        auto tmp = helper.rbegin()->second.back();
        helper.rbegin()->second.pop_back();
        if (helper[rtn].empty()) helper.erase(rtn);
        
        // 维护list链表, list是双向链表，不用手动操作了
        v.erase(tmp);
        return rtn;
    }

private:
    list<int> v;
    map<int, vector<list<int>::iterator>> helper;
};

int main(int argc, const char * argv[]) {
    int rtn;
    list<int> test{1,2};

    MaxStack1 gua1;
    gua1.push(79);
    rtn = gua1.pop();
    cout << "expect value = 79, actual value = " << rtn << endl;

    gua1.push(14);
    gua1.push(67);
    gua1.push(19);
    gua1.push(-92);

    rtn = gua1.popMax();
    cout << "expect value = 67, actual value = " << rtn << endl;

    MaxStack gua;
    gua.push(5);
    gua.push(1);
    gua.push(5);
    
    rtn = gua.top();
    cout << "expect value = 5, actual value = " << rtn << endl;
    
    rtn = gua.popMax();
    cout << "expect value = 5, actual value = " << rtn << endl;

    rtn = gua.top();
    cout << "expect value = 1, actual value = " << rtn << endl;
    
    rtn = gua.peekMax();
    cout << "expect value = 5, actual value = " << rtn << endl;
    
    rtn = gua.pop();
    cout << "expect value = 1, actual value = " << rtn << endl;
    
    rtn = gua.top();
    cout << "expect value = 5, actual value = " << rtn << endl;
    
    return 0;
}


#include <iostream>
#include <vector>

using namespace std;

/* Definition for singly-linked list. */
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    // Runtime: 76 ms, faster than 80.75%
    // Memory Usage: 45.5 MB, less than 5.26%
    vector<int> nextLargerNodes(ListNode* head) {
        // 递归可以搞定的，来一波迭代吧
        vector<int> st;
        vector<int> rtn, vals;
        // int size = 0;
        ListNode *next = head; //* prev = NULL,
        while (next) {
            // 中间的while进行单调栈的处理
            rtn.push_back(0);
            vals.push_back(next->val);
            
            while (st.size() && vals[st.back()] < next->val) {
                rtn[st.back()] = next->val;
                st.pop_back();
            }
            st.push_back(rtn.size()-1);
            // rtn.push_back(next->val);
            
            // 最后的更新next以维持while循环
            next = next->next;
        }
        
        return rtn;
    }
};

ostream &operator<< (ostream &os, vector<int> & rtn) {
    os << "[";
    for (auto item : rtn)
        os << item << ",";
    
    os << "]";
    return os;
}

int main(int argc, const char * argv[]) {
    Solution gua;
    ListNode *root = NULL;
    vector<int> rtn;
    
    ListNode *e5 = new ListNode(5);
    ListNode *e1 = new ListNode(1, e5);
    root = new ListNode(2, e1);
    rtn = gua.nextLargerNodes(root);
    cout << "expect value = [5,5,0], actual value = " << rtn << endl;

    ListNode *r5 = new ListNode(5);
    ListNode *r3 = new ListNode(3, r5);
    ListNode *r4 = new ListNode(4, r3);
    ListNode *r7 = new ListNode(7, r4);
    root = new ListNode(2, r7);
    rtn = gua.nextLargerNodes(root);
    cout << "expect value = [5,5,0], actual value = " << rtn << endl;

    ListNode *s1 = new ListNode(1);
    ListNode *s5 = new ListNode(5, s1);
    ListNode *s2 = new ListNode(2, s5);
    ListNode *s9 = new ListNode(9, s2);
    ListNode *ss1 = new ListNode(1, s9);
    ListNode *ss5 = new ListNode(5, ss1);
    ListNode *s7 = new ListNode(7, ss5);
    root = new ListNode(2, s7);
    rtn = gua.nextLargerNodes(root);
    cout << "expect value = [5,5,0], actual value = " << rtn << endl;
    return 0;
}


#include <iostream>
#include <queue>
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
    //Runtime: 16 ms, faster than 99.59%
    //Memory Usage: 13.3 MB, less than 91.47%
    struct myCmp {
        bool operator()(ListNode* A, ListNode* B) {
            return A->val > B->val;
        } // 题目要求升序排列，top是最小值，所以要用<
    };
    
    // 复习一下经典的merge K有序结构，核心是放入heap的每个node除了带有val
    // 还要带有到达当前有序结构下一个位置的信息，例如next指针；如果仅仅是K个数组咋办？
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        priority_queue<ListNode*, vector<ListNode*>, myCmp> helper;
        for (auto head : lists) {
            // 因为可能出现很贱的测试用例[[],[]]，所以这里必须增加入参保护
            if (head)
                helper.push(head);
        }
        ListNode* rtn = NULL, *prev = NULL;
        while (helper.size()) {
            ListNode* tmp = helper.top();
            helper.pop();
            if (!rtn) rtn = tmp;// 初始化rtn
            
            if (prev) {
                // 大意了，忘记更新next指针了。。。
                prev->next = tmp;
                // 大意啦大意啦！！！！
                prev = tmp;
            } else {
                prev = tmp;
            }
            
            if (tmp && tmp->next) {
                helper.push(tmp->next);
            }
        }
        return rtn;
    }
};

ostream & operator<<(ostream & os, ListNode* node) {
    os << "[";
    ListNode* cur = node;
    while (cur) {
        os << cur->val << ", ";
        cur = cur->next;
    }
    return os << "]";
}

int main(int argc, const char * argv[]) {
    // insert code here...
    Solution gua;
    ListNode* rtn;
    vector<ListNode*> lists;
    
    ListNode* h1 = new ListNode(1);
    h1->next = new ListNode(4);
    h1->next->next = new ListNode(5);
    
    ListNode* h2 = new ListNode(1);
    h2->next = new ListNode(3);
    h2->next->next = new ListNode(4);

    ListNode* h3 = new ListNode(2);
    h3->next = new ListNode(6);

    lists = vector<ListNode*>{NULL, NULL};
    rtn = gua.mergeKLists(lists);
    cout << rtn << endl;
    
    lists = vector<ListNode*>{h1,h2,h3};
    rtn = gua.mergeKLists(lists);
    cout << rtn << endl;
    return 0;
}


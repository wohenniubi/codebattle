
#include <iostream>

using namespace std;

/*Definition for singly-linked list.*/
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    // Runtime: 4 ms, faster than 97.17%
    // Memory Usage: 8.2 MB, less than 76.71%
    // 就是新旧两个链表头，然后不断从旧链表头部摘取出来一个，然后插入到新链表的头部
    ListNode* reverseList(ListNode* head) {
        ListNode* newHead = NULL;

        while (head) {
            ListNode* tmp = head->next;
            head->next = newHead;
            newHead = head;
            head = tmp;
        }
        return newHead;
    }
};

ostream &operator<<(ostream &os, ListNode* rtn) {
    os << "[";
    while (rtn) {
        cout << rtn->val << ", ";
        rtn = rtn->next;
    }
    os << "]";
    return os;
}

ListNode * generator(int N) {
    ListNode* rst = NULL;
    ListNode* pre = NULL;
    for (int i =0; N >=0 && i < N; i++) {
        ListNode* tmp = new ListNode(i+1);
        if (!rst) {
            rst = tmp;
            pre = tmp;
        } else {
            pre->next = tmp;
            pre = tmp;
        }
    }
    return rst;
}

int main(int argc, const char * argv[]) {
    Solution gua;
    ListNode* rtn;
    
    ListNode* e1 = generator(5);
    cout << "Before odd even swap:\n" << e1 << endl;
    rtn = gua.reverseList(e1);
    cout << "after  odd even swap:\n" << rtn << endl;
    return 0;
}



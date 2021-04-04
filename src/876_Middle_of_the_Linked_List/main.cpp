
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
    ListNode* middleNode(ListNode* head) {
        // 快慢指针
        ListNode *fast = head, *slow = head;
        while (fast && fast->next) {
            fast = fast->next->next;
            slow = slow->next;
        }
        // 跳出循环时，slow指向的就是所需节点
        return slow;
    }
};

int main(int argc, const char * argv[]) {
    Solution gua;
    ListNode * root = NULL;
    ListNode * rtn;
    
    ListNode *e5 = new ListNode(5);
    ListNode *e4 = new ListNode(4, e5);
    ListNode *e3 = new ListNode(3, e4);
    ListNode *e2 = new ListNode(2, e3);
    root = new ListNode(1, e2);
    rtn = gua.middleNode(root);
    cout << "expect value = 3, actual value = " << rtn->val << endl;

    ListNode *r6 = new ListNode(6);
    ListNode *r5 = new ListNode(5, r6);
    ListNode *r4 = new ListNode(4, r5);
    ListNode *r3 = new ListNode(3, r4);
    ListNode *r2 = new ListNode(2, r3);
    root = new ListNode(1, r2);
    rtn = gua.middleNode(root);
    cout << "expect value = 4, actual value = " << rtn->val << endl;

    return 0;
}


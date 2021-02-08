
#include <iostream>
#include <functional>

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
    //Runtime: 0 ms, faster than 100.00%
    //Memory Usage: 11.4 MB, less than 85.21%
    ListNode* deleteDuplicates(ListNode* head) {
        // 稍微不一样，要删除所有存在重复的node，还是两种办法：(1) 当作树处理
        // 或者(2) 快慢指针，dummy(用于返回) + lhs(用于前驱) + rhs(用于循环)
        
        // 傻了傻了，完全理解错了！！
        // function<ListNode*(ListNode*, int)> delNodeVal = [&](ListNode* head, int val)->ListNode* {
        //     if (!head) return head;
        //     // 现在head有效，判断与val的关系
        //     if (head->val == val) {
        //         ListNode* tmp = head;
        //         head = head->next;
        //         delete tmp;
        //         head = delNodeVal(head, val);
        //     } else {
        //         head->next = delNodeVal(head->next, val);
        //     }
        //     return head;
        // };
        // return delNodeVal(head, 300);

        if (!head || !(head->next)) return head;
        
        ListNode *kid = head->next;
        if (head->val == kid->val) {
            int val = head->val;
            while (head && head->val == val) {
                ListNode *tmp = head;
                head = head->next;
                delete tmp;// 这里持续循环的删除head
            }
            // 跳出while表明head为NULL，或者head->val !- vak
            return deleteDuplicates(head);
        } else {
            head->next = deleteDuplicates(kid);
            return head;
        }
    }
};

ostream & operator<< (ostream &os, ListNode* rtn) {
    os << "[";
    while (rtn) {
        os << rtn->val << ", ";
        rtn = rtn->next;
    }
    
    os << "]";
    return os;
}

int main(int argc, const char * argv[]) {
    Solution gua;
    ListNode* rtn;
    
    ListNode* p5 = new ListNode(5);
    ListNode* p4 = new ListNode(4, p5);
    p4 = new ListNode(4, p4);
    ListNode* p3 = new ListNode(3, p4);
    p3 = new ListNode(3, p3);
    ListNode* p2 = new ListNode(2, p3);
    ListNode* p1 = new ListNode(1, p2);
    cout << "before delete: " << p1 << endl;
    rtn = gua.deleteDuplicates(p1);
    cout << "after  delete: " << rtn << endl;

    return 0;
}

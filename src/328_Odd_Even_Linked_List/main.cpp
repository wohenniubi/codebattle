
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
    // Runtime: 8 ms, faster than 92.59%
    // Memory Usage: 10.6 MB, less than 25.39%
    // 这下试一试迭代写法，拆分为两个链表，要考虑保存头尾
    ListNode* oddEvenList(ListNode* head) {
        if (!head || !(head->next)) return head;
        
        // 好啦，现在head至少有两个节点
        ListNode* odd = head;
        ListNode* even = head->next;
        ListNode* evenhead = even;
        
        // 然后开始处理，由于even靠后，所以更容易出现NULL，因此作为while的循环判断
        // 如果even->next为空，说明链表总长度是偶数长度；even为空说明链表总长度为奇数长度，两种情况都意味着循环结束
        while (even && even->next) {
            // 1->2->3->4
            odd->next = odd->next->next;// 1->3
            even->next = even->next->next;// 2->4
            // 然后为了保证循环继续进行，更新odd和even
            odd = odd->next;
            even = even->next;// 突然想到even改变，所以要保存最初的even
        }
        // 跳出while循环之后odd还停留在最后一个节点，正好合适
        odd->next = evenhead;
        return head;//odd虽然改变，但是head不变，所以直接返回
    }
    
    // Runtime: 12 ms, faster than 63.63%
    // Memory Usage: 10.4 MB, less than 70.16%
    ListNode* oddEvenList1(ListNode* head) {
        // 解决办法，递归，然后使用两个链表，然后再合并两个链表，有点像是后续遍历
        if (!head || !(head->next)) return head;
        
        // 现在至少有两个节点啦
        ListNode* lhs = head;
        ListNode* rhs = head->next;
        
        ListNode* mid = dfsHelper(lhs, rhs, rhs->next);
        mid->next = rhs;
        return lhs;
    }
    
    // 之所以返回一个pair，是因为我打算用两个链表，然后首尾相连，那么就需要一个链表头，一个链表尾部
    ListNode* dfsHelper(ListNode* lhs, ListNode* rhs, ListNode* head) {
        // lhs和rhs一定要有值啊
        if (!head) {
            return lhs;
        }
        
        lhs->next = head;
        rhs->next = head->next;// 如果head->next等于NULL了，那么右边也就空了
        
        return dfsHelper(lhs->next, rhs->next, (rhs->next)?rhs->next->next: NULL);
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
    rtn = gua.oddEvenList(e1);
    cout << "after  odd even swap:\n" << rtn << endl;
    return 0;
}

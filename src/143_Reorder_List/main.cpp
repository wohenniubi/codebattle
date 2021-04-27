
#include <iostream>
#include <memory>

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
    pair<ListNode*,ListNode*> reverse(ListNode* head) {
        if (!head || !head->next) {
            return {head, head};
        }
        
        auto [nHead, lNode] = reverse(head->next);
        
        lNode->next = head;
        head->next = NULL;// 打断最后一个节点
        return {nHead, head};
    }

    //Runtime: 48 ms, faster than 12.89%
    //Memory Usage: 22.6 MB, less than 5.17%    
    void reorderList(ListNode* head) {
        if (!head->next) return;// 不需要翻转啦
        
        // 本题是找中点和翻转的综合
        ListNode *fast = head, *slow = head;
        while (fast && fast->next) {
            fast = fast->next->next;
            slow = slow->next;
        }
        // 此时slow后面接的就是剩下一半list的开始，两个序列肯定是head的长度大于等于shead的长度
        ListNode *shead = slow->next;
        slow->next = NULL;
        
        // 现在把shead翻转一下
        tie(shead, std::ignore) = reverse(shead);
        
        // 现在开始merge head和shead
        unique_ptr<ListNode> dummy(new ListNode);
        ListNode* prev = dummy.get();
        
        while (head || shead) {
            prev->next = head;
            head = head->next;
            
            prev = prev->next;
            prev->next = NULL;//打断摘除的head头节点
            
            // 两个序列肯定是head的长度大于等于shead的长度
            if (shead) {
                prev->next = shead;
                shead = shead->next;
                
                prev = prev->next;
                prev->next = NULL;// 打断摘除的shead头节点
            }
        }
        
        return;// dummy.get()->next;
    }
};

ostream & operator<<(ostream &os, ListNode* head) {
    os << "[";
    while (head) {
        os << head->val << ",";
        head = head->next;
    }
    
    os << "]";
    return os;
}

int main(int argc, const char * argv[]) {
    Solution gua;
    ListNode* e4 = new ListNode(4);
    ListNode* e3 = new ListNode(3,e4);
    ListNode* e2 = new ListNode(2,e3);
    ListNode* e1 = new ListNode(1,e2);
    gua.reorderList(e1);
    cout << "expect result = [1,4,2,3], actual result = " << e1 << endl;

    ListNode* r5 = new ListNode(5);
    ListNode* r4 = new ListNode(4,r5);
    ListNode* r3 = new ListNode(3,r4);
    ListNode* r2 = new ListNode(2,r3);
    ListNode* r1 = new ListNode(1,r2);
    gua.reorderList(r1);
    cout << "expect result = [1,5,2,4,3], actual result = " << r1 << endl;

    return 0;
}


#include <memory>
#include <map>
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
    //Runtime: 20 ms, faster than 72.27%
    //Memory Usage: 10.9 MB, less than 5.68%
    ListNode* insertionSortList(ListNode* head) {
        if (!head) return head;

        // 便于二分快速查找到对应的位置，ListNode*存的是前指针，所以需要一个dummy
        unique_ptr<ListNode> dummy(new ListNode(INT_MIN, head));
        ListNode* lastptr = head;
        multimap<int,ListNode*> helper{{head->val, dummy.get()}};

        ListNode *cur = head->next; //用于循环
        head->next = NULL;

        // 按照insertion sort的机制，先插入到最后，再找到合适的位置，然后插入
        while (cur) {
            // 遍历原始链表，每次摘除头节点，加入rtn
            ListNode* tmp = cur;
            cur = cur->next;

            // 旧节点已经彻底分离，现在开始加入dummy为首的list
            tmp->next = NULL;

            // tmp->next = dummy->next;// 更新一下
            auto iter = helper.upper_bound(tmp->val);//upper_bound要好一些，这样一旦iter有效，就可以不用判断lastptr
            if (iter == helper.end()) {
                // helper[tmp->val] = lastptr; // 没有>tmp->val的值了，tmp应该加入helper并放在最后，作为新的lastptr
                helper.emplace(tmp->val, lastptr); // 别大意multimap没有定义[]
                lastptr->next = tmp;
                lastptr = tmp;
            } else { // 找到了一个>tmp->val的值，

                // 也正好iter->存放的是前一个node，multimap插入时也放在相等值的最右侧，刚好匹配
                helper.emplace(tmp->val, iter->second);//auto niter =
                tmp->next = iter->second->next;// tmp的后继节点要修改为这个iter->second->next
                iter->second->next = tmp; // 原本的iter的前驱节点的下一个节点变成了当前tmp
                iter->second = tmp; // 原本的iter的前驱节点也更新为tmp
            }
        }

        // ListNode* rtn = dummy->next;
        // delete dummy;
        return dummy->next; //rtn;
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

int main() {
    Solution gua;
    ListNode *rtn;
    
    ListNode* e3 = new ListNode(3);
    ListNode* e1 = new ListNode(1, e3);
    ListNode* e2 = new ListNode(2, e1);
    ListNode* e4 = new ListNode(4, e2);
    
    rtn = gua.insertionSortList(e4);
    cout << "expect result = [1,2,3,4], actual result = " << rtn << endl;

    ListNode* r0 = new ListNode(0);
    ListNode* r4 = new ListNode(4, r0);
    ListNode* r3 = new ListNode(3, r4);
    ListNode* r5 = new ListNode(5, r3);
    ListNode* r_1 = new ListNode(-1, r5);
    
    rtn = gua.insertionSortList(r_1);
    cout << "expect result = [-1,0,3,4,5], actual result = " << rtn << endl;

    return 0;
}



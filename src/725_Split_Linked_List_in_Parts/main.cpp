
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
    // 这个工厂用于从head这个链表里面提取(remain+k-1)/k个节点到rtn中，然后根据其定义，可以嵌套调用
    //Runtime: 8 ms, faster than 65.13%
    //Memory Usage: 8.9 MB, less than 43.84%
    void splitFactory(ListNode* head, int remain, int k, vector<ListNode*> &rtn) {
        if (!head) {
            // 如果链表为空，那么就把剩余的部分全部填上NULL，如果resize，那么可以直接返回
            return; //rtn.insert(k, NULL);
        }
        
        int cnt = (remain + k-1)/k;
        remain -= cnt;// 提前减去cnt，要不然后面cnt被弄成0了
        rtn[rtn.size()-k] = head;// rtn.size()-k是倒序，首先把头节点保存下来
        ListNode* prev = NULL;
        while (cnt) {
            prev = head;
            head = head->next;
            --cnt;
        }
        prev->next = NULL;// 打断之前的部分
        // splitFactory(head, remain - cnt, k-1, rtn);// 然后递归操作, 大意了大意了！！cnt已经为0了
        splitFactory(head, remain, k-1, rtn);// 然后递归操作, 大意了大意了！！cnt已经为0了
    }
    
    vector<ListNode*> splitListToParts(ListNode* head, int k) {
        // 想象一个工厂（元操作），需要哪些信息才能完成操作，以及针对要求的关键一点：本题是每次提取多少个node
        vector<ListNode*> rtn = vector<ListNode*>(k);
        int remain = 0;
        ListNode* tmp = head;
        while (tmp) {
            tmp = tmp->next;
            remain++;
        }
        
        splitFactory(head, remain, k, rtn);
        return rtn;
    }
};

ostream & operator<< (ostream &os, vector<ListNode*> &rtn) {
    os << "[";
    for (auto path : rtn) {
        os << "[";
        while (path) {
            os << path->val << ", ";
            path = path->next;
        }
        os << "], ";
    }
    os << "]";
    return os;
}

int main(int argc, const char * argv[]) {
    Solution gua;
    vector<ListNode*> rtn;
    int k;

    cout << "\nTest 1:" << endl;
    ListNode* e10 = new ListNode(10);
    ListNode* e9 = new ListNode(9, e10);
    ListNode* e8 = new ListNode(8, e9);
    ListNode* e7 = new ListNode(7, e8);
    ListNode* e6 = new ListNode(6, e7);
    ListNode* e5 = new ListNode(5, e6);
    ListNode* e4 = new ListNode(4, e5);
    ListNode* e3 = new ListNode(3, e4);
    ListNode* e2 = new ListNode(2, e3);
    ListNode* e1 = new ListNode(1, e2);
    rtn = gua.splitListToParts(e1, k=3);
    cout << rtn << endl;

    cout << "\nTest 2:" << endl;
    ListNode* r3 = new ListNode(3);
    ListNode* r2 = new ListNode(2, r3);
    ListNode* r1 = new ListNode(1, r2);
    rtn = gua.splitListToParts(r1, k=5);
    cout << rtn << endl;

    return 0;
}

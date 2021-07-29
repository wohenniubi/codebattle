
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
    ListNode* swapPairs(ListNode* head) {
        if (!head) return head;
        // 这个不就是swap N node的低配版吗
        
        // 先找到下下个邻居，如果没有，那么就返回了
        ListNode* nexthead = head->next;
        if (!nexthead) return head;
        nexthead = nexthead->next;
        
        // 如果找到了，那么就对[head,nexthead)这个区间的节点进行交换，以nexthead作为结束位置
        // 这里就是while循环的swap，拆分为两部分，一部分循环，一部分作为新的list，每次从头加入
        ListNode* prev = nexthead;//NULL; 
        // 因为需要知道nexthead之前的那个节点，这个不就是head吗，而head在while中被修改，所以先保存下来
        ListNode* last = head;
        
        while (head != nexthead) {
            // 把head从旧链接摘下来，处理前保留head的下一个
            ListNode* tmp = head->next;
            
            // 这个head会从头部插入到prev的链表里面
            head->next = prev;
            // 原本这里要判断初次进入时，head->next要指向nexthead;
            // 之后都直接使用prev，因此这里把prev初始化为nexthead，则非常精妙的完成操作
            prev = head;
            
            head = tmp;//为了while循环正确执行，这里head进行更新
        }
        last->next = swapPairs(nexthead);
        return prev;
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
    rtn = gua.swapPairs(e1);
    cout << "after  odd even swap:\n" << rtn << endl;
    return 0;
}


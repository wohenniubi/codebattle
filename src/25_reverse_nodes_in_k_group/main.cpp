#include <iostream>

using namespace std;

/* Definition for singly-linked list. */
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    // 思路1: 大致还是divide & conquer思路,每次只reverse k这个部分的链表,preorder DFS
    // 思路2~: 先采用比较直观的递归调用方式,递归的话函数接口包括输入和返回
    //        输入可能是链表头,k值,k之后的链表尾部; 返回可能是链表整体的头
    // 思路3~: 由于是单向链表,为了获得链表尾部,得有一次循环操作; 思路3~需要与思路2~迭代
    // 思路4: 最终决定将遍历k个节点的操作放在递归函数里面, 这样输入就可以不需要考虑链表尾
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode* tmp = helper(head, k);
        return tmp;
    }

    ListNode* helper(ListNode* head, int k) {
        ListNode *cur = head;
        // 把head到cur之间到这部分节点当作二叉树里面的中间节点, 然后现对它进行处理
        // 所以是pre order DFS
        // (1) 遍历k个节点, 如果不足k, 此时的head就是最终的head
        for (int i=0; i<k; i++) {
            if (!cur) return head;
            // 注意cur指向的是k长度链之外(特别强调)的那个node
            cur = cur->next;
        }

        // (2) 处理当前"节点", 即reverse k个链表node
        ListNode *new_head = reverse(head, cur);
        // 注意new_head是先前k长度链之中最后的node

        // (3) 处理叶子结点, 即链表剩下的部分
        ListNode *rst_head = reverseKGroup(cur, k);
        // 注意1: 要从k长度链之外的那个node开始
        // 注意2: 还要将rst_head添加翻转之后的new_head链表的尾部
        //       这里精妙绝伦的地方来了, 并没有再循环一次而是利用了head
        //       因为reverse之后, 原本head指向的节点已变为k个链表段的最后节点
        head->next = rst_head;

        return new_head;
    }

    // reverse的接口: 输入应该包括链表头和尾, 不清楚怎么搞先传这两个值进去
    // 输出应该是调整好之后的链表头; 注意原本的tail后面的连接不要丢失了
    ListNode* reverse(ListNode* head, ListNode* tail) {
        // 这里是已知链表头尾, 对链表进行的翻转; 有点loop的感觉
        ListNode* pre = tail;
        while (head != tail) {
            ListNode *tmp = head->next;
            head->next = pre;
            pre = head;
            head = tmp;
        }
        // 太经典了, 返回的是pre!!!!
        return pre;
    }
};

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

int main() {
    int k;
    Solution gua;
    // case1
    ListNode* head1 = generator(k=5);
    ListNode* rst = gua.reverseKGroup(head1, k=2);
    ListNode* tmp = rst;
    while (tmp) {
        cout << tmp->val << "->";
        tmp = tmp->next;
    }
    cout << endl;

    cout << "finish!" << endl;
    return 0;
}
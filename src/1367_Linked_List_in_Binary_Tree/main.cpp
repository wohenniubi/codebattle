
#include <iostream>

using namespace std;

//Definition for singly-linked list.*/
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

//Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    // 觉得这道题有点像backtracking，限制条件如下
    //1 <= node.val <= 100 for each node in the linked list and binary tree.
    //The given linked list will contain between 1 and 100 nodes.
    //The given binary tree will contain between 1 and 2500 nodes.
    // 以下代码对于某个case 会超时，原因不明，猜测可能是在isSubPath递归返回false时继续计算导致了大量重复的操作
//    bool isSubPath(ListNode* head, TreeNode* root) {
//        //return helper(head, root); 貌似递归函数的入参与这个函数一致
//        // 返回条件
//        if (!head) return true;
//        if (!root) return false;
//
//        // 原本的for loop被具体化为三个操作，左右分支和mid节点
//        if (head->val == root->val) {
//            bool isLhs = (isSubPath(head->next,root->left) || isSubPath(head, root->left));
//            if (isLhs) return true;
//            bool isRhs = (isSubPath(head->next,root->right) || isSubPath(head, root->right));
//            return isRhs;
//        } else {
//            bool isLhs = (isSubPath(head, root->left));
//            if (isLhs) return true;
//            bool isRhs = (isSubPath(head, root->right));
//            return isRhs;
//        }
//        return false;
//    }
    
    //Runtime: 48 ms, faster than 88.51%
    //Memory Usage: 32.4 MB, less than 10.97%
    // 非常巧妙的递归，思路差不多一致，但是却可以通过，猜测基本原因是让递归以O(n)的方式运行，整体复杂度O(|L|*|T|)
    bool isSubPath(ListNode* head, TreeNode* root) {
      if (!root) return false;
      return isPath(head, root) || isSubPath(head, root->left) || isSubPath(head, root->right);
    }

    // 这个函数仅仅判断当前link list是否match，每次都会减少list的长度，因此不会超过O(|L|)
    bool isPath(ListNode* head, TreeNode* root) {
      if (!head) return true;
      if (!root) return false;
      if (root->val != head->val) return false;
      return isPath(head->next, root->left) || isPath(head->next, root->right);
    }
};

int main(int argc, const char * argv[]) {
    Solution gua;
    bool rtn;
    
    TreeNode *root1 = new TreeNode(1);
    TreeNode *r1_2_l4 = new TreeNode(4);
    TreeNode *r1_2_r4 = new TreeNode(4);
    root1->left = r1_2_l4; root1->right = r1_2_r4;
    TreeNode *r1_3_l2 = new TreeNode(2);
    TreeNode *r1_3_r2 = new TreeNode(2);
    r1_2_l4->right = r1_3_l2; r1_2_r4->left = r1_3_r2;
    TreeNode *r1_4_l1 = new TreeNode(1);
    TreeNode *r1_4_r6 = new TreeNode(6);
    TreeNode *r1_4_r8 = new TreeNode(8);
    r1_3_l2->left = r1_4_l1; r1_3_r2->left = r1_4_r6; r1_3_r2->right = r1_4_r8;
    ListNode *head1 = new ListNode(4), *h1_k2 = new ListNode(2), *h1_k8 = new ListNode(8);
    head1->next = h1_k2; h1_k2->next = h1_k8;
    
    rtn = gua.isSubPath(head1, root1);
    cout << "expect value = 1, actual value = " << rtn << endl;
    return 0;
}

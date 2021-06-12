
#include <iostream>

using namespace std;

/* Definition for a binary tree node.*/
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
    // 该函数用于从根节点开始逐一比较两棵树
    bool dfsCmp(TreeNode* root, TreeNode* subRoot) {
        if (!root || !subRoot)
            return root == subRoot; //对于某个树为空，另一个不为空的情况，返回false，空树是自己的subtree

        if (root->val != subRoot->val)
            return false;
        return dfsCmp(root->left, subRoot->left)
            && dfsCmp(root->right, subRoot->right);
    }
    
    // 主函数主要作用是找到和subRoot值相同的点；
    //Runtime: 12 ms, faster than 99.29%
    //Memory Usage: 28.8 MB, less than 88.91%
    bool isSubtree(TreeNode* root, TreeNode* subRoot) {
        if (!root || !subRoot)
            return root == subRoot; //对于某个树为空，另一个不为空的情况，返回false，空树是自己的subtree

        // 现在两个树都不为空了，先序遍历
        if (root->val == subRoot->val) {
            if (dfsCmp(root->left, subRoot->left)
                && dfsCmp(root->right, subRoot->right))
                return true;
        }
        // 不能提前退出，还得继续检查，不过会不会重复计算啊。。。
        return (isSubtree(root->left, subRoot) || isSubtree(root->right, subRoot));
    }
};

int main(int argc, const char * argv[]) {
    Solution gua;
    bool rtn;
    
    TreeNode * r1 = new TreeNode(1);
    TreeNode * r2 = new TreeNode(2);
    TreeNode * r4 = new TreeNode(4, r1, r2);
    TreeNode * r5 = new TreeNode(5);
    TreeNode * r3 = new TreeNode(3, r4, r5);
    
    TreeNode * s1 = new TreeNode(1);
    TreeNode * s2 = new TreeNode(2);
    TreeNode * s4 = new TreeNode(4, s1, s2);
    rtn = gua.isSubtree(r3, s4);
    cout << "expect value = 1, actual value = " << rtn << endl;

    r2->left = new TreeNode(0);
    rtn = gua.isSubtree(r3, s4);
    cout << "expect value = 0, actual value = " << rtn << endl;

    return 0;
}

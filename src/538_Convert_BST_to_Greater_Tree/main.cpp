#include <iostream>
#include <queue>
#include <functional>

using namespace std;

/* Definition for a binary tree node. */
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
    //Runtime: 88 ms, faster than 5.00%
    //Memory Usage: 34.7 MB, less than 50.43%
    TreeNode* convertBST(TreeNode* root) {
        // 从Example1看来，这里可以用中序遍历解决，先遍历右分支的那种，那就来吧
        // 试想一下，如果没有这个图，直接问，把BST中每个node的值修改为大于它的所有node的value之和，还能够反应出来是这道题吗
        int sum = 0;
        
        // 如果使用全局变量的话，就只需要一个入参；
        // 如果不需要全局变量，那么需要一个int入参和一个int返回，下次试试这个吧
        function<void(TreeNode*)> inorderSum = [&](TreeNode* root)->void {
            // 返回条件
            if (!root) return;
            
            // root有效，先进行右分支
            inorderSum(root->right);
            
            // 中间节点进行处理
            sum += root->val;
            root->val = sum;// root->val就是比它大的所有数的sum了
            
            // 再进行左分支处理
            inorderSum(root->left);
        };
        
        inorderSum(root);
        return root;
    }
};

ostream & operator<<(ostream &os, TreeNode* root) {
    os << "[";
    deque<TreeNode*> helper{root};
    while (helper.size()) {
        int size = helper.size();
       
        string level = "";
        bool isValid = false; 
        for (int i = 0; i < size; ++i) {
            TreeNode* tmp = helper.front();
            helper.pop_front();
            
            if (tmp) {
                isValid = true;
                level.append(to_string(tmp->val)).append(",");
                if (tmp->left || tmp->right) {
                  helper.push_back(tmp->left);
                  helper.push_back(tmp->right);
                }
            } else {
              level.append("null,");
            }
        }
        if (isValid)
          os << level;
    }
    
    os << "]";
    return os;
}

int main(int argc, const char * argv[]) {
    Solution gua;
    TreeNode* rtn;

    TreeNode* n4 = new TreeNode(4);
    TreeNode* n1 = new TreeNode(1);
    TreeNode* n6 = new TreeNode(6);
    TreeNode* n0 = new TreeNode(0);
    TreeNode* n2 = new TreeNode(2);
    TreeNode* n5 = new TreeNode(5);
    TreeNode* n7 = new TreeNode(7);
    TreeNode* n3 = new TreeNode(3);
    TreeNode* n8 = new TreeNode(8);

    n4->left = n1; n4->right = n6;
    n1->left = n0; n1->right = n2;
    n6->left = n5; n6->right = n7;
    n2->right = n3; n7->right = n8;

    rtn = gua.convertBST(n4);
    cout << rtn << endl;

    return 0;
}


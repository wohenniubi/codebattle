
#include <iostream>
#include <vector>

using namespace std;

/*Definition for a binary tree node. */
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
    int maxCnt;
    //Runtime: 8 ms, faster than 89.16%
    //Memory Usage: 21.4 MB, less than 34.60%
    tuple<int,int,int> inOrder(TreeNode* root, bool &isBST) {
        // 返回条件
        if (!root) {
            isBST = true;
            // 分别是以root为根的tree的总节点个数，左分支最大数，右分支最小数
            return {0,INT_MIN,INT_MAX};
        }
        
        bool isValidL = false, isValidR = false;
        int rtn = 0, max_val = INT_MIN, min_val = INT_MAX;
        bool tmp = true;
        if (root->left) {
            auto [lnum, lmax, lmin] = inOrder(root->left, isValidL);
            if (isValidL && lmax < root->val) {
                rtn += lnum;
                min_val = min(min_val, lmin);
            } else {
                tmp = false;
                // return {0,0,0}; 不能立即返回
            }
        }
        if (root->right) {
            auto [rnum, rmax, rmin] = inOrder(root->right, isValidR);
            if (isValidR && root->val < rmin) {
                rtn += rnum;
                max_val = max(max_val, rmax);
            } else {
                isBST = false;
                return {0,0,0};
            }
        }
        // 能够坚持到这里说明满足条件
        if (tmp == false) {
            isBST = false;
            return {0,0,0};
        }
        isBST = true;
        maxCnt = max(maxCnt, rtn+1);
        if (!root->left)  min_val = root->val;
        if (!root->right)  max_val = root->val;
        return {rtn+1, max_val, min_val};
    }
   
    // Runtime: 16 ms, faster than 37.45% 
    // Memory Usage: 30.4 MB, less than 6.46%
    vector<int> dfs(TreeNode* root) {
        if (!root) {
            // 分别是最小值和最大值，可以完美的解决上一层的左分支最大值，右分支最小值与root->val的比较
            return {0, INT_MAX, INT_MIN}; 
        }
        
        vector<int> lhs, rhs;
        lhs = dfs(root->left);
        rhs = dfs(root->right);
        if (root->val > lhs[2] && root->val < rhs[1]) {
            int cnt = lhs[0] + rhs[0] + 1;// 此时可以组成一个更大的BST
            maxCnt = max(maxCnt, cnt);
            int MAX = max(root->val, rhs[2]);
            int MIN = min(root->val, lhs[1]);// 可以完美解决叶子节点的情况
            return {cnt, MIN, MAX};
        }
        // if之外说明不是BST，此时返回INT_MIN和INT_MAX可以让上层的root->val > lhs[2]返回false，完美解决
        return {0, INT_MIN, INT_MAX};
    }
    
    int largestBSTSubtree(TreeNode* root) {
        // 树最让人满意的性质是每个节点相当于一个子问题，从这个子问题向更大的子问题迈进
        maxCnt = 0;
        //bool isBST = false;
        //inOrder(root, isBST);
        dfs(root);
        return maxCnt;
    }
};

int main(int argc, const char * argv[]) {
    Solution gua;
    int rtn;
    TreeNode* r1 = new TreeNode(1);
    TreeNode* r2 = new TreeNode(2, NULL, r1);
    TreeNode* r22 = new TreeNode(2, r2, NULL);
    TreeNode* r3 = new TreeNode(3);
    TreeNode* rT = new TreeNode(2, r22, r3);
    TreeNode* r5 = new TreeNode(5);
    TreeNode* r7 = new TreeNode(7, r5, NULL);
    TreeNode* r4 = new TreeNode(4, rT, r7);
    rtn = gua.largestBSTSubtree(r4);
    cout << "expect value = 2, actual value = " << rtn << endl;

    TreeNode* e5 = new TreeNode(5);
    TreeNode* e4 = new TreeNode(4);
    TreeNode* e3 = new TreeNode(3, e4, NULL);
    TreeNode* e2 = new TreeNode(2, NULL, e5);
    TreeNode* e1 = new TreeNode(1, e3, e2);
    rtn = gua.largestBSTSubtree(e1);
    cout << "expect value = 2, actual value = " << rtn << endl;

    return 0;
}

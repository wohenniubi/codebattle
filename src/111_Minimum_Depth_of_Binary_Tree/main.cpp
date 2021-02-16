
#include <iostream>
#include <queue>

using namespace std;
/**
 * Definition for a binary tree node. */
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
    //Runtime: 232 ms, faster than 76.72%
    //Memory Usage: 144.6 MB, less than 80.51%
    int minDepth(TreeNode* root) {
        // 层序遍历本质上是BFS哟
        deque<TreeNode*> helper{root};
        int minlvl = 0;
        if (!root) return minlvl;
        
        while (helper.size()) {
            int size = helper.size();
            minlvl++;
            
            for (int i = 0; i < size; ++i) {
                TreeNode* head = helper.front();
                helper.pop_front();
                
                // 到达leaf的操作
                if (!head->left && !head->right)
                    return minlvl;
                
                // 左右分支加入helper
                if (head->left) helper.push_back(head->left);
                if (head->right) helper.push_back(head->right);
            }
        }
        
        return minlvl;//应该不会跳出while
    }
};

int main(int argc, const char * argv[]) {
    Solution gua;
    TreeNode* n9 = new TreeNode(9);
    TreeNode* n15 = new TreeNode(15);
    TreeNode* n7 = new TreeNode(7);
    TreeNode* n20 = new TreeNode(20, n15, n7);
    TreeNode* n3 = new TreeNode(3,n9,n20);
    
    int rtn;
    rtn = gua.minDepth(n3);
    cout << "expect result = 2, actual result = " << rtn << endl;
    
    return 0;
}

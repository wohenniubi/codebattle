
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

/**
 Definition for a binary tree node.*/
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
    // 快忘记迭代的写法了。。。只好用递归
    void dfs(TreeNode* root, vector<int> & stk) {
        if (!root) return;
        if (root->left) dfs(root->left, stk);
        stk.push_back(root->val);
        if (root->right) dfs(root->right, stk);
    }
    
    //Runtime: 8 ms, faster than 42.00%
    //Memory Usage: 13.8 MB, less than 10.67%
    TreeNode* insertIntoMaxTree1(TreeNode* root, int val) {
        // 反正a的长度不超过100，那么硬上嘛
        // 基本思路先由A恢复这个a序列，把val添加到a后面
        // 再调用leetcode 654的construct函数构造这个B
        
        vector<int> arr;
        vector<TreeNode*> stk;// 用于遍历A时的存储，中序遍历
        dfs(root, arr);
        
        arr.push_back(val);
        // 现在开始重构B
        for (auto val : arr) {
            TreeNode* cur = new TreeNode(val);
            // 这个while是为了找到比当前val小的那个最大的node，这个node要位于cur的left
            // while (stk.size() && stk.back()->val < num) { //改了一次变量名，忘记同步修改了
            while (stk.size() && stk.back()->val < val) {
                cur->left = stk.back();
                stk.pop_back();//之后都是以cur为分割了，这个node可以被去掉了
            }
            // 区分一下stk是否为空; 不为空时最后一个node是比cur大的，那么cur要位于node的right
            if (stk.size())
                stk.back()->right = cur;
            
            // 暂存cur，之后的节点若是比cur大，那么会在while那里pop cur；
            // 如果比cur小，那么会在while之后被加到最后一个node的右边，然后存入stk里面
            stk.push_back(cur);
        }
        return stk.size()? stk.front():NULL;
    }
    
    // 结合leetcode的另一种解法，我改进了一下加入了dummy，不需要恢复原始序列a，一气呵成，鼓掌啊
    // 基本原理估计是利用了maximum tree的性质，root节点作为左右分支的分割， 那么就用val与每个root进行比较
    // 貌似还做了优化，使用的是失传已久的O(1)空间复杂度的迭代，酷炫啊
    TreeNode* insertIntoMaxTree(TreeNode* root, int val) {
        TreeNode* dummy = new TreeNode(INT_MAX);
        dummy->right = root;
        TreeNode *prev = dummy, *cur = root;
        
        TreeNode* n = new TreeNode(val);
        while (cur && cur->val > val) {
            // 因为新加入的val的顺序是最晚的，所以当它小于某个node时，
            // 必定是放在node的右边；这里利用了maximum Tree和加入顺序的性质
            prev = cur;
            cur = cur->right;
        }
        // 跳出while循环说明(1)cur为NULL；(2)找到了一个小于val的node
        // if (cur) {
        n->left = cur;
        // }// 对于cur为空的情况貌似没啥操作
        prev->right = n;
        
        return dummy->right;
    }
};

ostream & operator<<(ostream &os, TreeNode* root) {
    os << "[";
    deque<TreeNode*> helper{root};
    while (helper.size()) {
        int size = helper.size();
        
        for (int i = 0; i < size; ++i) {
            TreeNode* tmp = helper.front();
            helper.pop_front();
            
            os << (tmp? to_string(tmp->val) : "NULL") << ",";
            if (tmp) {
                helper.push_back(tmp->left);
                helper.push_back(tmp->right);
            }
//            os << tmp->val << ",";
//            if (tmp->left) helper.push_back(tmp->left);
//            if (tmp->right) helper.push_back(tmp->right);
        }
    }
    
    os << "]";
    return os;
}

int main(int argc, const char * argv[]) {
    Solution gua;
    TreeNode* rtn;
    
    vector<int> nums{3,2,1,6,0,5};
    TreeNode* root = new TreeNode(4);
    TreeNode* n1 = new TreeNode(1);
    TreeNode* n3 = new TreeNode(3);
    TreeNode* n2 = new TreeNode(2);
    root->left = n1; root->right = n3;
    n3->left = n2;
    
    int val;
    rtn = gua.insertIntoMaxTree(root, val=5);
    cout << rtn << endl;

    return 0;
}

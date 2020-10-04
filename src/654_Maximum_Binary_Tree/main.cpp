
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
    //Runtime: 112 ms, faster than 44.93%
    //Memory Usage: 42.8 MB, less than 32.88%
    TreeNode* constructMaximumBinaryTree1(vector<int>& nums) {
        // 思路是转化为子问题，然后拆分为两个子树分别处理
        // 在考量能否改进一点的地方是增加一个stack，用于来存储已经找到的最大值，这样避免重复搜索
        
        return helper(nums,0,nums.size());// 复杂度对于[1,1000]应该搞得定，大不了是O(n^2)
    }
    
    TreeNode* helper(vector<int>& nums, int bgn, int end) {
        int maxPos = bgn-1, maxVal = INT_MIN;
        // if (bgn < 0 || bgn >= nums.size()) return NULL; 大意了大意了啊！！！
        if (bgn < 0 || bgn >= end) return NULL;
        
        for (int i = bgn; i < end; ++i) {
            // 因为全部是unique值，所以没有等于的情况
            if (maxVal < nums[i]) {
                maxVal = nums[i];
                maxPos = i;
            }
        }
        
        TreeNode* root = new TreeNode(nums[maxPos]);
        TreeNode* l_node = helper(nums, bgn, maxPos);
        TreeNode* r_node = helper(nums, maxPos+1, end);
        
        root->left = l_node; root->right = r_node;
        return root;
    }
    
    // 另一种做法，非常巧妙：就是使用了stack来简化for遍历的操作，有点像中序遍历的迭代方法
    //Runtime: 108 ms, faster than 49.78% 
    //Memory Usage: 39.6 MB, less than 43.80%
    TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
        vector<TreeNode*> stk;
        for (int i = 0; i < nums.size(); ++i) {
            TreeNode* cur = new TreeNode(nums[i]);
            // 下面这个while循环是为了找到第一个比当前cur大的node，
            // 如果找到；那么cur必定属于这个node的右节点，因为node会分割左右；
            // 同时这个cur又会是那些比cur还小的node的父节点
            while (!stk.empty() && stk.back()->val < nums[i]) {
                cur->left = stk.back(); // 因为下面会被pop，所以先存下来；会一直更新到比cur小的那个最大的node
                stk.pop_back();
            }
            // 跳出while循环说明stack里面存的node都比当前node大（或者stack为空）
            // 对于栈不为空的情况，按照题意最大值的node为分割，那么当前node必定是之前那个node的右节点
            
            if (!stk.empty())
                stk.back()->right = cur;
            
            stk.push_back(cur);//为了防止下一个node比cur小，需要将cur也存入stack
        }
        return stk.front();
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
            
            os << tmp->val << ",";
            if (tmp->left) helper.push_back(tmp->left);
            if (tmp->right) helper.push_back(tmp->right);
        }
    }
    
    os << "]";
    return os;
}

int main(int argc, const char * argv[]) {
    Solution gua;
    TreeNode* rtn;
    
    vector<int> nums{3,2,1,6,0,5};
    rtn = gua.constructMaximumBinaryTree(nums);
    cout << rtn << endl;

    return 0;
}

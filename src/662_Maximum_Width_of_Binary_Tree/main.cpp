
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

/*Definition for a binary tree node.*/
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
    vector<long> ids;
    
    // 迭代的解法，有点难以想到
    int widthOfBinaryTree2(TreeNode* root) {
        if(root==nullptr) {
            return 0;
        }
        
        int ans = 0;
        queue< pair<TreeNode*,int> >q;
        q.emplace(root,1);
        
        while(!q.empty()){
            int size = q.size();
            int start = q.front().second;
            int end   = q.back().second;
            
            ans = max(ans, end-start +1);
            
            for(int i=0; i<size;i++){
                TreeNode* node = q.front().first;
                int idx = q.front().second-start;
                q.pop();
                
                if(node->left){
                    q.emplace(node->left,2*idx+1);
                }
                if(node->right){
                    q.emplace(node->right,2*idx+2);
                }
            }
        }
        
        return ans;
    }
    
    // 注意还是要使用long，因为对于example2这样的例子，如果depth很大，那么base的值会超过int的范围
    int dfs(TreeNode* root, int depth, long id) {
        if (!root) return 0;
        
        // 表明这是该层的第一个节点
        if (ids.size() == depth)
            ids.push_back(id);// 每一行只记录一个值，只记录当前层的最小id
        
        // 减去当前层最小的节点，即去掉偏置
        long base = id - ids[depth], rtn = 0; // 根节点id减去当前层的最小id，减完之后+1就是当前节点作为最右点时的宽度
        
        rtn = max(base+1, (long)dfs(root->left, depth+1, base*2));//base+1是从id到宽度的转换
        rtn = max(rtn, (long)dfs(root->right, depth+1, base*2+1));
        
        return rtn;
    }
    
    //Runtime: 20 ms, faster than 6.77%
    //Memory Usage: 17.9 MB, less than 8.87%
    int widthOfBinaryTree(TreeNode* root) {
        ids.clear();
        return dfs(root, 0, 0);
    }
};

int main(int argc, const char * argv[]) {
    Solution gua;
    
    int rtn;
    TreeNode *f9 = new TreeNode(1);
    TreeNode *f8 = new TreeNode(1, NULL, f9);
    TreeNode *f7 = new TreeNode(1, NULL, f8);
    TreeNode *f6 = new TreeNode(1, NULL, f7);
    TreeNode *f5 = new TreeNode(1, NULL, f6);
    TreeNode *f4 = new TreeNode(1, NULL, f5);
    TreeNode *f3 = new TreeNode(1, NULL, f4);
    TreeNode *f2 = new TreeNode(1, NULL, NULL);
    TreeNode *f1 = new TreeNode(1, f2, f3);
    rtn = gua.widthOfBinaryTree(f1);
    cout << "expect value = 2, actual value = " << rtn << endl;

    TreeNode *s6 = new TreeNode(6);
    TreeNode *s7 = new TreeNode(7);
    TreeNode *s5 = new TreeNode(5, s6, NULL);
    TreeNode *s9 = new TreeNode(9, NULL, s7);
    TreeNode *s3 = new TreeNode(3, s5, NULL);
    TreeNode *s2 = new TreeNode(2, NULL, s9);
    TreeNode *s1 = new TreeNode(1, s3, s2);
    rtn = gua.widthOfBinaryTree(s1);
    cout << "expect value = 8, actual value = " << rtn << endl;
    
    TreeNode *e5 = new TreeNode(5);
    TreeNode *e3 = new TreeNode(3);
    TreeNode *e9 = new TreeNode(9);
    TreeNode *es = new TreeNode(3, e5, e3);
    TreeNode *e2 = new TreeNode(2, NULL, e9);
    TreeNode *e1 = new TreeNode(1, es, e2);
    rtn = gua.widthOfBinaryTree(e1);
    cout << "expect value = 4, actual value = " << rtn << endl;

    return 0;
}

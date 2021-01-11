
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
    // 网上的fancy做法，基本思路与solution1类似，区别在于第3步，不是从子节点的任务考虑父节点的任务
    // 而是从父节点向子节点传递任务，这样让代码变得很简洁，牛逼！！
    bool isValidBST(TreeNode* root) {
        return helpisValidBST(root,LLONG_MAX,LLONG_MIN);
    }
    bool helpisValidBST(TreeNode* root, long max_num, long min_num){
        if(!root){
            return true;
        }
        if(root->val >= max_num){
            return false;
        }
        if(root->val <= min_num){
            return false;
        }
        return helpisValidBST(root->left, root->val, min_num) && helpisValidBST(root->right, max_num, root->val);
    }
};

class Solution1 {
public:
    //Runtime: 16 ms, faster than 63.99%
    //Memory Usage: 22.7 MB, less than 7.37%
    bool isValidBST(TreeNode* root) {
        // 思路还是一样：
        // 1.先把每个节点当作处理，
        // 2.想这个节点需要做哪些事才能完成题目要求，比较root和左右分支的val；
        // 3.然后想想这些事同样由parent node来执行能不能完成题目的要求；
        //   发现parent node仅仅比较左右分支不得行，比如Example2；
        // 4.返回到第2步，扩展每个节点的任务，比如返回最小值和最大值
        //   这样root与左边最大值进行比较，与右边最小值进行比较；
        //   第3步parent也做同样操作，可以搞定
        // 5.如果第4步还不行，返回到1步，把多个节点当作一个group进行考虑，思考2～4步
        // 6 做完之后把限制条件再考虑一遍，很可能全是坑啊
        function<bool(TreeNode*, pair<int,int>&)> checkValid
            = [&](TreeNode* root, pair<int,int>& minMax)->bool {
            if (!root)
                return true;//是否需要改动minMax
            else if (!root->left && !root->right) {
                minMax = make_pair(root->val, root->val);
                return true;
            }
            
            // 来吧分析左分支
            // pair<int,int> minMaxLhs{root->val, root->val-1};// 有最极端的case。。。所以不能减1
            pair<int,int> minMaxLhs{root->val, root->val};
            if (root->left && !checkValid(root->left, minMaxLhs)) {
                return false;
            } else {
                // 说明左分支不存在，或者存在且是BST，不论如何，只使用minMaxLhs.second
                // 尼玛，题目没有说存在duplicate value的情况。。。那就得加上等号
                // if (minMaxLhs.second > root->val)
                // if (minMaxLhs.second >= root->val)
                if (root->left && minMaxLhs.second >= root->val)
                    return false;
            }
            
            // 来吧分析右分支
            // pair<int,int> minMaxRhs{root->val+1, root->val};// 有最极端的case。。。所以不能加1
            pair<int,int> minMaxRhs{root->val, root->val};
            if (root->right && !checkValid(root->right, minMaxRhs)) {
                return false;
            } else {
                // 说明右分支不存在，或者存在且是BST，不论如何，只使用minMaxRhs.first
                // 尼玛，题目没有说存在duplicate value的情况。。。那就得加上等号
                // if (minMaxRhs.first < root->val)
                // if (minMaxRhs.first <= root->val)
                if (root->right && minMaxRhs.first <= root->val)
                    return false;
            }
            
            // 中间节点处理，更新minMax
            minMax = make_pair(minMaxLhs.first, minMaxRhs.second);
            return true;
        };
        
        pair<int,int> minMax;
        return checkValid(root, minMax);
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
    bool rtn;

    // 好特么贱，居然有这个case
    TreeNode *j1 = new TreeNode(-2147483648);
    TreeNode *j2 = new TreeNode(-2147483648);
    j1->left = j2;
    rtn = gua.isValidBST(j1);
    cout << j1 << endl;
    cout << "expect value = 0, actual value = " << rtn << endl;
    
    TreeNode *d1 = new TreeNode(1);
    TreeNode *d2 = new TreeNode(1);
    d1->left = d2;
    rtn = gua.isValidBST(d1);
    cout << d1 << endl;
    cout << "expect value = 0, actual value = " << rtn << endl;
    
    TreeNode *n2 = new TreeNode(2);
    TreeNode *n1 = new TreeNode(1);
    TreeNode *n3 = new TreeNode(3);
    n2->left = n1; n2->right = n3;
    rtn = gua.isValidBST(n2);
    cout << n2 << endl;
    cout << "expect value = 1, actual value = " << rtn << endl;

    TreeNode *p5 = new TreeNode(5);
    TreeNode *p1 = new TreeNode(1);
    TreeNode *p4 = new TreeNode(4);
    TreeNode *p3 = new TreeNode(3);
    TreeNode *p6 = new TreeNode(6);
    p5->left = p1; p5->right = p4;
    p4->left = p3; p4->right = p6;
    rtn = gua.isValidBST(p5);
    cout << p5 << endl;
    cout << "expect value = 0, actual value = " << rtn << endl;

    return 0;
}



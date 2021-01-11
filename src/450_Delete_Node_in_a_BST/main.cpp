
#include <iostream>
#include <functional>
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
    //看看别人网上的操作，整体函数返回的是运行后的根节点
    TreeNode* deleteNode(TreeNode* root, int key) {
        if (!root) return NULL;// TODO: 返回条件

        // 这样的框架写法让代码更简洁
        if (root->val == key) {
            TreeNode* rtn = NULL;
            // 开始删除操作，适当分析可以简化操作;
            if (!root->left) {
                // 如果左分支为空，那么直接用右分支替换root
                rtn = root->right;
                delete root;
                return rtn;
            }
            if (!root->right) {
                // 如果右分支为空，那么直接用左分支替换root
                rtn = root->left;
                delete root;
                return rtn;//NULL; 咋回事，写了个null？？
            }
            // 左右分支都不为空，那么寻找左分支的最大值(或者右分支的最小值)
            TreeNode *prev = root, *next = root->left;
            while (next && next->right) {
                prev = next;
                next = next->right;
            }
            // 此时的while循环，跳出只可能表明next->right为null，因为初始化的next不可能为NULL
            
            if (1) {
                // 还可以直接优化，再继续调用自己;
                root->val = next->val;
                // root->left = deleteNode(root->left, key);//大意啦，此时要删除next->val而不是key
                root->left = deleteNode(root->left, next->val);
            } else {
                if (prev == root) {
                    // 说明必然是next->right == null，因为next初始化为root->left，必然不为null
                    // 那么直接用这个next的val替换root，再删除next就好
                    root->val = next->val;
                    root->left = next->left;
                    delete next;
                } else {
                    // 说明必然是next->right == null（next绝不为NULL，因为next初始化不为NULL，
                    // 它为null只可能来自于while内部的next->right，而如果后者为null，它连while都进不去）
                    // 此时要用这个next的左分支更新prev的右分支
                    root->val = next->val;
                    prev->right = next->left;
                    delete next;
                }
            }
        } else if (root->val < key) {
            // 右分支处理
            // 处理结束之后更新一下右分支
            root->right = deleteNode(root->right, key);
        } else {
            // 左分支处理
            // 处理之后更新一下左分支
            root->left = deleteNode(root->left, key);
        }
        return root;
    }
    
    //Runtime: 116 ms, faster than 6.19%
    //Memory Usage: 34.4 MB, less than 43.56%
    TreeNode* deleteNode1(TreeNode* root, int key) {
        // 本题稍微难一点因为要先找到需要删除的节点，如果没有找到那就结束，对于找到的节点进行删除操作；
        // 删除的时候还是一样的思路，先把每个节点当作一个节点，然后想这个节点要做什么事，然后想其父节点或者子节点要做什么事，e.g.维持BST
        // 对于维持BST，有不同种的pattern，于是需要总结出一种pattern下的特征操作；我们要尽量举一些看似是同一种pattern的例子，然后总结规律
        // 有时候总结不出规律不是题目难，而是因为举的例子刚好属于两个pattern，或者一个节点信息不够用等等...这些就要多练习了
        
        // BST的查找小菜吧，要不使用迭代试试
        TreeNode *cur = root;
        TreeNode *dummy = new TreeNode(INT_MAX);//又加个参数，因为后续可能会修改pre的左右分支，要是pre为null，那不就瓜了
        dummy->left = root;
        TreeNode *pre = dummy;//这个是写到后面才想起的补充，可以不用从root再遍历一遍，省时间
        while (cur && cur->val != key) {
            pre = cur;
            if (cur->val > key)
                cur = cur->left;
            else
                cur = cur->right;//必然是右分支了
        }
        // 跳出while说明cur为空或者找到
        if (!cur) return root;//不需要删除任何节点，直接返回root，包括root为null的情况
        
        // 接下来的处理交给左右分支解决
        TreeNode* parent = cur;
        TreeNode* target = cur->left;
        // 先找cur的左分支里面的最大值来替换cur
        while (target && target->right) {
            parent = target;
            target = target->right;
        }
        // 跳出时target为null或者target为左分支最大值
        if (target) {
            if (parent == cur) {
                //那么就让target的左分支街上parent节点的左分支
                parent->left = target->left;
                //然后用target替换cur这个node
                cur->val = target->val;
            } else {
                parent->right = target->left;
                cur->val = target->val;
            }
            delete target;
            return root;
        }
        
        parent = cur;
        target = cur->right;
        // 找到右分支的最小值
        while (target && target->left) {
            parent = target;
            target = target->left;
        }
        if (target) {
            if (parent == cur) {
                parent->right = target->right;
                parent->val = target->val;
            } else {
                parent->left = target->right;
                cur->val = target->val;
            }
            delete target;
            return root;
        }
        
        // cur没有左右分支
        if (pre->left == cur)
            pre->left = NULL;
        else
            pre->right = NULL;
        delete cur;
        TreeNode* rtn = dummy->left;
        delete dummy;
        return rtn;
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

    TreeNode* n5 = new TreeNode(5);
    TreeNode* n3 = new TreeNode(3);
    TreeNode* n6 = new TreeNode(6);
    TreeNode* n2 = new TreeNode(2);
    TreeNode* n4 = new TreeNode(4);
    TreeNode* n7 = new TreeNode(7);
    n5->left = n3; n5->right = n6;
    n3->left = n2; n3->right = n4;
    n6->right = n7;
    rtn = gua.deleteNode(n5, 3);

    cout << rtn << endl;
    return 0;
}


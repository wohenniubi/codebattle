
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
  TreeNode* insertIntoBST(TreeNode* root, int val) {
    // 这次尝试新的做法，如果插入的比root大，且在左右分支之间，替换原始root；
    // 再把原始的root当作新增节点加入，比较适合于node在原始树中不存在的情况，要不然有点小操作
    // 另外：强BST，一般右分支大于等于root都可以吧
    TreeNode* node = new TreeNode(val);
    function<TreeNode* (TreeNode*, TreeNode*)> helper
      = [&](TreeNode* root, TreeNode* node)->TreeNode* {
      if (!root) return node;

      //来吧开始处理中间节点
      if (root->val < node->val) {
        if (root->right && root->right->val > node->val) {
          //用node替换root;再让左分支继续处理
          swap(node->val, root->val);//大意了大意了，需要交换两者的值，而不是指针！！！
          //node->left = root->left; root->left = NULL;
          //node->right = root->right; root->right = NULL;
          //因为可能会发生替换，所以要更新left
          //node->left = helper(node->left, root);
          root->left = helper(root->left, node);
        } else {
          //root->right不存在或者右分支不大于(不存在重复的话就是小)
          root->right = helper(root->right, node);//交给右分支迭代处理
        }
      } else {
        // root不小于node;不存在重复的话，root大于node
        // 交给左分支继续迭代处理
        root->left = helper(root->left, node);
      }
      return root;
    };

    return helper(root, node);
  }
};

ostream& operator <<(ostream& os, TreeNode* root) {
  os << "[";
  deque<TreeNode*> st{ root };
  while (st.size()) {
    int size = st.size();

    bool isValid = false;
    string level;
    for (int i = 0; i < size; ++i) {
      TreeNode* tmp = st.front();
      st.pop_front();

      if (tmp) {
        isValid = true;
        os << tmp->val << ",";
        if (tmp->left || tmp->right) {
          st.push_back(tmp->left);
          st.push_back(tmp->right);
        }
      } else {
        os << "null,";
      }
    }
    if (isValid)
      os << level;
  }

  os << "]";
  return os;
}

int main() {
  Solution gua;
  TreeNode* rtn;

  TreeNode* n4 = new TreeNode(4);
  TreeNode* n2 = new TreeNode(2);
  TreeNode* n1 = new TreeNode(1);
  TreeNode* n3 = new TreeNode(3);
  TreeNode* n7 = new TreeNode(7);

  n4->left = n2; n4->right = n7;
  n2->left = n1; n2->right = n3;
  rtn = gua.insertIntoBST(n4, 5);

  cout << rtn << endl;
  cout << "Hello World!\n";
}


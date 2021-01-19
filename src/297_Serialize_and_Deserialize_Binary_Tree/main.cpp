#include <iostream>
#include <queue>
#include <sstream>

using namespace std;

/*Definition for a binary tree node.  */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Codec {
public:
    // runtime 72ms beats 29.70% of cpp submissions
    // memory usage 39.4MB beats 36.06% of cpp submissions
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        // 确实如果不包含空节点的话，仅有某一种顺序的节点，是无法恢复出tree的
        // 但是如果保存了NULL节点，那么接收端采用同样的顺序就一定可以顺利恢复——这一点我也学习了
        if (!root) return "#";
        
        // 采用先序处理
        string rtn = to_string(root->val);
        string lhs = serialize(root->left);
        string rhs = serialize(root->right);
        
        rtn.append(",").append(lhs).append(",").append(rhs);
        return rtn;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        istringstream is(data);
        string t = "";
        deque<string> vals;
        
        while (getline(is,t,',')) {
            vals.push_back(t);
        }
        
        // 现在直接开始先序处理
        // function<TreeNode*(vector<string>&)> preOrder = [&](vector<string> &vals)->TreeNode* { 别大意啊
        function<TreeNode*(deque<string>&)> preOrder = [&](deque<string> &vals)->TreeNode* {
            if (vals.empty()) return NULL;
            string val = vals.front();
            vals.pop_front();
            if (val == "#") {
                return NULL;
            }
            
            // 先序处理
            // TreeNode* root(int(val)); C++居然不能这么用，哎
            // TreeNode* root(stoi(val)); 用Python久了。。。
            TreeNode* root = new TreeNode(stoi(val));
            root->left = preOrder(vals);
            root->right = preOrder(vals);
            return root;
        };
        return preOrder(vals);
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

int main() {
  Codec gua;
  TreeNode* n1 = new TreeNode(1);
  TreeNode* n2 = new TreeNode(2);
  TreeNode* n3 = new TreeNode(3);
  TreeNode* n4 = new TreeNode(4);
  TreeNode* n5 = new TreeNode(5);
  n1->left = n2; n1->right = n3;
  n3->left = n4; n3->right = n5;

  TreeNode* rtn = gua.deserialize(gua.serialize(n1));
  cout << rtn << endl;

  return 0;
}



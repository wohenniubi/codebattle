
#include <iostream>
#include <sstream>
#include <vector>
#include <queue>

using namespace std;

/*Definition for a binary tree node.*/
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Codec {
public:
    //Runtime: 36 ms, faster than 54.16%
    //Memory Usage: 27.6 MB, less than 52.33%
    // 复杂代码还是先用递归来搞，搞通一个可行解之后再使用iterative进行适当优化
    void encode(TreeNode* root, string &s) {
        if (!root) {
            // s.push_back('#'); // 对于BST来讲，可以省略空节点的符号，利用BST特性来确定是左右分支
            return;
        }
        // 采用先序遍历
        string tmp = to_string(root->val);
        s.insert(s.end(), tmp.begin(), tmp.end());
        s.push_back('.'); // root和kid的数据还是要区分一下
        
        encode(root->left, s);
        encode(root->right, s);
        return;
    }
    
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        // 来联系一下哇，必须加上空节点，否则仅凭一棵树的某种遍历方式是不能恢复出来的
        if (!root) return "";//"#"; BST的话就可以直接返回空
        string rtn;
        encode(root, rtn);
        return rtn;
    }
    
    TreeNode* decode(deque<string> &st, int minVal, int maxVal) {
        if (st.empty()) return NULL;
        int val = stoi(st.front());
        if (val < minVal || val > maxVal) return NULL;
        
        st.pop_front();
        TreeNode *rtn = new TreeNode(val);
        rtn->left = decode(st, minVal, val);
        rtn->right = decode(st, val, maxVal);
        return rtn;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        deque<string> st;
        istringstream is(data);
        string tmp = "";
        
        // 接收端也采用先序遍历，不过由于借助了istream，这是个while操作，所以要使用iterative的方式，用一个stack
        while (getline(is, tmp, '.')) {
            st.push_back(tmp);
        }
        int minVal = -1, maxVal = 10001;
        return decode(st, minVal, maxVal);
    }
};

// Your Codec object will be instantiated and called as such:
// Codec* ser = new Codec();
// Codec* deser = new Codec();
// string tree = ser->serialize(root);
// TreeNode* ans = deser->deserialize(tree);
// return ans;

ostream & operator<<(ostream &os, TreeNode* root) {
    os << "[";
    deque<TreeNode*> helper{root};
    while (helper.size()) {
        int size = helper.size();
        
        for (int i = 0; i < size; ++i) {
            TreeNode* tmp = helper.front();
            helper.pop_front();
            
            if (tmp) {
                os << tmp->val << ",";
                if (tmp->left) helper.push_back(tmp->left);
                if (tmp->right) helper.push_back(tmp->right);
            }
        }
    }
    
    os << "]";
    return os;
}

int main(int argc, const char * argv[]) {
    Codec gua;
    TreeNode* rtn;

    TreeNode* r4 = new TreeNode(4);
    TreeNode* r3 = new TreeNode(3);
    TreeNode* r2 = new TreeNode(2);
    TreeNode* r1 = new TreeNode(1);
    r1->right = r2;
    r3->left = r1; r3->right = r4;
    rtn = gua.deserialize(gua.serialize(r3));
    cout << "expect result = [3,1,4,null,2], actual result = " << rtn << endl;

    TreeNode* e1 = new TreeNode(1);
    TreeNode* e3 = new TreeNode(3);
    TreeNode* e2 = new TreeNode(2);
    e2->left = e1; e2->right = e3;
    rtn = gua.deserialize(gua.serialize(e2));
    cout << "expect result = [2,1,3], actual result = " << rtn << endl;
    
    rtn = gua.deserialize(gua.serialize(NULL));
    cout << "expect result = [], actual result = " << rtn << endl;

    return 0;
}

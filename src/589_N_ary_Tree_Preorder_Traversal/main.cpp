
#include <iostream>
#include <vector>

using namespace std;

/* Definition for a Node.*/
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};

class Solution {
public:
    //Runtime: 24 ms, faster than 40.18%
    //Memory Usage: 11.2 MB, less than 75.98%
    vector<int> preorder(Node* root) {
        vector<int> rtn;
        if (!root) return rtn;
        
        // 最简单的还是递归，不过试一试stack的iterative
        vector<Node*> st{root}; // 当做一个栈
        while (st.size()) {
            // 取出一个node
            Node* tmp = st.back();
            st.pop_back();// 从后面取出一个节点

            // 处理这个节点
            rtn.push_back(tmp->val);
            
            // for (int i = tmp->children.size()-1; i >= 0; --i) {
            //    if (tmp->children[i]) {
            for (auto iter = tmp->children.rbegin(); iter != tmp->children.rend(); ++iter) {
                if (*iter) {
                    st.push_back(*iter); // tmp->children[i]
                }
            }
            
            // 下面是二叉树的操作
//             // 由于栈是先进后出，为了保证下次末尾还是左节点，所以要先放右节点
//             if (tmp->right)
//                 st.push_back(tmp->right);
//             if (tmp->left)
//                 st.push_back(tmp->left);
        }
        return rtn;
    }
};

ostream &operator<< (ostream &os, vector<int> &rtn) {
    os << "[";
    for (auto val : rtn)
        os << val << ", ";
    
    os << "]";
    return os;
}

int main(int argc, const char * argv[]) {
    Solution gua;
    vector<int> rtn;
    Node* e5 = new Node(5);
    Node* e6 = new Node(6);
    Node* e3 = new Node(3, {e5,e6});
    Node* e2 = new Node(2);
    Node* e4 = new Node(4);
    Node* e1 = new Node(1, {e3,e2,e4});

    rtn = gua.preorder(e1);
    cout << "\nTest1\n" << rtn << endl;
    return 0;
}

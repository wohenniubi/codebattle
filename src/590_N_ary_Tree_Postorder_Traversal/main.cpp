
#include <iostream>
#include <vector>

using namespace std;

/* Definition for a Node.  */
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
    // 递归写法
    // Runtime: 28 ms, faster than 28.02%
    // Memory Usage: 10.9 MB, less than 100.00%
    void dfs(Node* root, vector<int> &rtn) {
        if (!root) return;
        
        for (auto iter = begin(root->children); iter != end(root->children); ++iter) {
            if (*iter)
                dfs(*iter, rtn);
        }
        rtn.push_back(root->val);
    }
    
    vector<int> postorder(Node* root) {
        vector<int> rtn;
        dfs(root, rtn);
        return rtn;
    }
    
    // 迭代写法
    // Runtime: 24 ms, faster than 40.87%
    // Memory Usage: 11.2 MB, less than 80.21% 
    vector<int> postorder1(Node* root) {
        vector<int> rtn;
        if (!root) return rtn;// 极端情况
        
        vector<Node*> st{root};
        while (st.size()) {
            Node* tmp = st.back();
            st.pop_back();
            
            // 处理当前节点，很特殊的处理
            rtn.push_back(tmp->val);
            
            // 与先序遍历不同，这里是先放左边，这样最右边的节点先出来，最后再对rtn进行reverse操作
            for (auto iter = tmp->children.begin(); iter != tmp->children.end(); ++iter) {
                if (*iter)
                    st.push_back(*iter);
            }
        }
        
        reverse(begin(rtn), end(rtn));//别忘了postorder要倒序一下
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

    rtn = gua.postorder(e1);
    cout << "\nTest1\n" << rtn << endl;
    return 0;
}



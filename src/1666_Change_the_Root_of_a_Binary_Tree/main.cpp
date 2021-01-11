
#include <iostream>
#include <queue>

using namespace std;

// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* parent;
};

class Solution {
public:
    // leetcode的解答，充分利用了parent指针，这么牛逼的吗？
    // 由于具有parent指针，基本思路是从leaf开始向着root node进行反转，直奔主题
    Node* flipBinaryTree(Node* root, Node * leaf) {
        // 本身就是根节点，那就不转了
        if (leaf->parent==NULL) return leaf;
        Node *cur = leaf, *p = cur->parent;
        //Node *pp = p->parent;
        
        leaf->parent = NULL;
        while (p != NULL) {
            cur->left = p;
            if (cur == p->left)
                p->left = NULL;// 如果节点是原始父节点的左分支，则摘取左分支
            else
                // 如果节点是原始父节点的右分支，则将左分支摘取到右分支；对于root节点到话，不要交换
                p->right = (p==root)?NULL: p->left;//cur; 别大意啊！！
            Node* pp = p->parent;
            p->parent = cur;//更新parent节点为找到的节点
            
            // 然后是对于循环的控制，将原本的p作为当前的cur，然后原本的p作为pp
            cur = p;
            p = pp;
            //pp = p->parent;
        }
        return leaf;
    }
    
    //Runtime: 4 ms, faster than 79.28%
    //Memory Usage: 8 MB, less than 79.73%
    Node* flipBinaryTree1(Node* root, Node * leaf) {
        // 从Example的图看明白了（没有看解释），貌似规律就是：如果目标叶子节点A
        // (1) 是父节点B的左子节点，那么直接把父节点B作为节点A的左子节点；然后以父节点B作为返回（此时B是个缺少左支的节点）
        // (2) 是父节点B的右子节点，那么把父节点B作为节点A的左子节点，然后把父节点原本的左分支作为右分支，然后返回节点B
        // 不论如何返回的B都是个缺少左分支的节点
        
        // 首先是遍历到leaf，使用栈一路保存父节点信息
        function<Node*(Node*,Node*)> changeRoot = [&](Node* root, Node* leaf) -> Node* {
            // 返回条件
            if (root == NULL) return NULL;
            if (root == leaf) {
                // 在找到指定节点之前就是进行dfs查找，一旦找到开始回溯;
                root->parent = NULL;//很蛋疼，为啥要有parent pointer？？
                return root;
            }
            
            // 左分支操作
            Node* lhs = changeRoot(root->left, leaf);
            if (lhs) {
                root->left = NULL;
                root->parent = lhs;// 忘记更新parent pointer了
                lhs->left = root;
                return root;
            }
            
            // 右分支操作
            Node* rhs = changeRoot(root->right, leaf);
            if (rhs) {
                //root->right = root->left; 好蛋疼的题目，对于root还要特别处理
                root->right = (root->parent)? root->left: NULL;// 对于root节点，就不用交换了
                root->left = (root->parent)? NULL: root->left;// 仅对于root节点，将左分支摘取到右边
                root->parent = rhs;// 忘记更新parent pointer了
                rhs->left = root;
                return root;
            }
            return NULL;// 若是没有找到，那就返回空
        };
        
        changeRoot(root, leaf);
        return leaf;
    }
};

ostream & operator<<(ostream &os, Node* root) {
    os << "[";
    // 基于BFS的树遍历
    deque<Node*> st{{root}};
    while (st.size()) {
        int size = st.size();
        bool isValid = false;
        string level;
        for (int i = 0; i < size; ++i) {
            Node* tmp = st.front();
            st.pop_front();
            level += (tmp? to_string(tmp->val):"null");
            level.append((i!=size-1), ',');
            
            isValid |= (tmp != NULL);// 标记一下如果有有效的值
            if (tmp) {
                st.push_back(tmp->left);
                st.push_back(tmp->right);
            }
        }
        if (isValid) os << level;
        if (st.size()) os << ",";
    }
    
    os << "]";
    return os;
}

int main(int argc, const char * argv[]) {
    Solution gua;
    Node *n3 = new Node(); n3->val = 3;
    Node *n5 = new Node(); n5->val = 5;
    Node *n1 = new Node(); n1->val = 1;
    Node *n6 = new Node(); n6->val = 6;
    Node *n2 = new Node(); n2->val = 2;
    Node *n0 = new Node(); n0->val = 0;
    Node *n8 = new Node(); n8->val = 8;
    Node *n7 = new Node(); n7->val = 7;
    Node *n4 = new Node(); n4->val = 4;
    n3->left = n5; n3->right = n1; n3->parent = NULL;
    n5->left = n6; n5->right = n2; n5->parent = n3;
    n1->left = n0; n1->right = n8; n1->parent = n3;
    n6->left = NULL; n6->right = NULL; n6->parent = n5;
    n2->left = n7; n2->right = n4; n2->parent = n5;
    n7->left = NULL; n7->right = NULL; n7->parent = n2;
    n4->left = NULL; n4->right = NULL; n4->parent = n2;
    n0->left = NULL; n0->right = NULL; n0->parent = n1;
    n8->left = NULL; n8->right = NULL; n8->parent = n1;
    
    Node *rtn = gua.flipBinaryTree(n3, n7);
    cout << "expect result = [7,2,null,5,4,3,6,null,null,null,1,null,null,0,8,], actual result = " << rtn << endl;

//    Node *rtn = gua.flipBinaryTree(n3, n0);
//    cout << "expect result = [0,1,null,3,8,5,null,null,null,6,2,null,null,7,4,], actual result = " << rtn << endl;

    return 0;
}


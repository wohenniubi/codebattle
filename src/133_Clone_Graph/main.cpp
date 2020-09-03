#include <iostream>
#include <unordered_map>
#include <vector>

#include <unordered_set>

using namespace std;

/* Definition for a Node. */
class Node {
public:
    int val;
    vector<Node*> neighbors;
    
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};

//Runtime: 24 ms, faster than 11.01%
//Memory Usage: 9.3 MB, less than 6.66%
class Solution {
public:
    // 采用DFS的办法进行处理，函数的返回值就是clone后的节点
    Node* cloneGraph(Node* node) {
        return helper(node);
    }
private:
    // 因为是graph的遍历，要有个visited，就以每个node的val作为key
    unordered_map<int, Node*> visited;
    Node* helper(Node* node) {
        if (!node) return NULL;
        
        if (visited.count(node->val)) return visited[node->val];
        
        Node *rtn = new Node(node->val);
        visited[node->val] = rtn;//相当于标记为访问

        for (auto adj : node->neighbors) {
            Node* tmp = helper(adj);
            rtn->neighbors.push_back(tmp);
        }
        // visited[node->val] = rtn; 此时才放入visited会出现死循环吧
        return rtn;
    }
};

// 网上的做法，和我的方法本质是一样的，区别是他们用的是旧graph的指针为key，
// 这样做的好处是可以允许node的val重复
class Solution2 {
public:
    Node* cloneGraph(Node* node) {
        // Iterative DFS
            // How to handle cycles?
                // bool function
            // NOPE !!!
            // HASHU MAPPUH
                // Check for duplicate
        if (!node)
            return nullptr;
        // Only push value we have not seen before
        if (umap.find(node) == umap.end()) {
            umap[node] = new Node(node->val, {});// Node(int val, vector<Node*> _neighbors)
            for (Node* neighbor : node->neighbors) {
                umap[node]->neighbors.emplace_back(cloneGraph(neighbor));
            }
        }
        return umap[node];
    }
    
private:
    unordered_map<Node*, Node*> umap;
};

// 这个其实是个遍历graph的函数
ostream & operator << (ostream & os, Node* node) {
    os << "[";
    vector<Node*> helper{node};
    unordered_set<Node*> visited;
    
    while (helper.size()) {
        Node* tmp = helper.front();
        helper.erase(helper.begin());
        
        if (!tmp || visited.count(tmp)) continue;// 大意了，得在这里判断tmp是否为NULL
        visited.insert(tmp);
        
        // 遍历这个node的所有邻居
        os << "[";
        for (auto adj : tmp->neighbors) {
            os << to_string(adj->val) << ",";
        }
        os << "], ";
    }
    
    os << "]";
    return os;
}

int main(int argc, const char * argv[]) {
    Solution gua, gua1, gua2, gua3;
    
    Node* rtn;
    rtn = gua.cloneGraph(NULL);
    cout << rtn << endl;

    Node* node1 = new Node(1);
    rtn = gua1.cloneGraph(node1);
    cout << rtn << endl;
    
    Node* node2_1 = new Node(1);
    Node* node2_2 = new Node(2);
    node2_1->neighbors.push_back(node2_2);
    node2_2->neighbors.push_back(node2_1);
    rtn = gua2.cloneGraph(node2_1);
    cout << rtn << endl;
    
    Node* node3_1 = new Node(1);
    Node* node3_2 = new Node(2);
    Node* node3_3 = new Node(3);
    Node* node3_4 = new Node(4);
    node3_1->neighbors.push_back(node3_2);
    node3_1->neighbors.push_back(node3_4);
    node3_2->neighbors.push_back(node3_1);
    node3_2->neighbors.push_back(node3_3);
    node3_3->neighbors.push_back(node3_2);
    node3_3->neighbors.push_back(node3_4);
    node3_4->neighbors.push_back(node3_1);
    node3_4->neighbors.push_back(node3_3);
    rtn = gua3.cloneGraph(node3_1);
    cout << rtn << endl;
    
    return 0;
}


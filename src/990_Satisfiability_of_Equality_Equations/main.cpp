#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    class UF {
    public:
        UF (int n) {
            parent.resize(n);
            for (int i = 0; i < n; ++i) parent[i]=i;
        }
        int find(int p) {
            // 找到p的parent
            int x = p;
            while (parent[x] != x) {
                parent[x] = parent[parent[x]];// 路经压缩 
                x = parent[x];// 进行下一次循环
            }
            return x;
        }
        // void union(int p, in q) { // 避免与关键字union冲突
        void unite(int p, int q) {
            int parentP = find(p);
            int parentQ = find(q);
            if (parentP == parentQ) return;
            // 这里默认把第二个输入q的parent设置为p
            parent[parentQ] = parentP;
        }
        bool isConnected(int p, int q) {
            return find(p) == find(q);
        }
    private:
        vector<int> parent;
        // 就不搞分支平衡的size了 
    };
    
    bool equationsPossible(vector<string>& equations) {
        // 根据昨天的思路，本题使用union find来做
        // 先为每个char创建一个parent索引，当==时就union，当!=时就判断parent是否union，矛盾则返回false
        UF helper(26);
        
        // 现在开始解析equations, 先对所有==的公式判断连通性，再对所有!=的公式判断是否连通性失败，不完整的判断是不对的
        for (auto & eq : equations) {
            if ('=' == eq[1]) {
                int p = eq[0]-'a', q = eq[3]-'a';
                helper.unite(p, q);
            }
        }
        
        for (auto & eq : equations) {
            if ('!' == eq[1]) {
                int p = eq[0]-'a', q = eq[3]-'a';
                if (helper.isConnected(p,q)) return false;
            }
        }
        
        //int rtn = true; 下面代码没搞对
        // for (auto & eq : equations) {
        //     int p = eq[0]-'a', q = eq[3]-'a';
        //     bool isEq = eq[1] == '=';
        //     int parentP = helper.find(p);
        //     int parentQ = helper.find(q);
        //     if (isEq) {
        //         // 如果p和q其中有一方没有被设置过
        //         if (parentP == p || parentQ == q) {
        //             helper.union(p, q);
        //         }
        //         if (parentP != parentQ) return false;
        //     } else {
        //         if (parentP == parentQ) return false;
        //     }
        // }
        return true;
    }
};

int main() {
  Solution gua;
  bool rtn;

  vector<string> equations{"a==b","b!=a"};
  rtn = gua.equationsPossible(equations);
  cout << "expect value = 0, actual value = " << rtn << endl;

  equations = vector<string>{"a==b","b==c","a==c"};
  rtn = gua.equationsPossible(equations);
  cout << "expect value = 1, actual value = " << rtn << endl;

  return 0;
}


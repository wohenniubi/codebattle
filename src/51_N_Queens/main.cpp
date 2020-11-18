#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    #define ROW 0
    #define COL 1
    #define SLA 2
    #define BAK 3

    // 最好还是设置一个宏，免得搞错之后满篇改
    #define chkBit(x,y) ((x) & 1<<(y))
    #define setBit(x,y) ((x) |= 1<<(y))
    #define clkBit(x,y) ((x) &= ~(1<<(y)))

    //Runtime: 4 ms, faster than 98.03%
    //Memory Usage: 7.5 MB, less than 84.86%
    vector<vector<string>> solveNQueens(int n) {
        // backtracking的经典问题，试着做一下吧
        vector<vector<string>> rtn;
        vector<string> path;
        // 还需要一个visited数组用于pruning掉不满足条件的值
        vector<int> visited(4);
        
        findAllSols(path, n, visited, rtn);
        return rtn;
    }
    
    // 来吧，战胜自己; 因为是找到所有的solution，那么去重复的操作也可以不用了
    void findAllSols(vector<string> &path, int n, vector<int> &visited, vector<vector<string>> &rtn) {
        int size = path.size();
        if (size == n) {
            rtn.push_back(path);// 此时path满足条件，加入rtn中
            return;
        }

        // 不同于leetcode 698，那里需要传入一个pos作为for loop的起点，
        // 一方面是因为backtracking的复杂度为O(n^n)，那道题的n最高为16，16^16还是有点大
        // 另一方面因为那道题是选择一个集合，集合意味着从左到右for loop时，一旦top的loop选择了某个元素，
        // 越bottom的loop只需要选择pos右侧剩余的item就好，再对pos左侧的item进行选择会造成重复，
        for (int i = 0; i < n; ++i) {
            // 从每一行的最左边遍历到最右边，n个move决策
            if (!checkValid(visited, path.size(), i, n))  continue;
            
            // 设置flag
            setValid(visited, path, i, n);
            
            // 中序处理节点
            findAllSols(path, n, visited, rtn);
                
            // 恢复flag
            resetValid(visited, path, i, n);
        }
    }
    
    bool checkValid(vector<int> &visited, int row, int col, int n) {
        // 检查行是否OK;
//        if (visited[ROW] & ((row+1)<<1)) return false;
//        if (visited[COL] & ((col+1)<<1)) return false;
//        // 对于/的情况，某个bit等于x+y+1的值, 例如: (0,0)在第1bit，(1,0)和(0,1)在第2bit，(0,2),(1,1)和(2,0)在弟3个bit，总共2*n-1
//        if (visited[SLA] & ((row+col+1)<<1)) return false;
//        // 对于\的情况，某个bit等于x-y+n的值, 例如：(0,3)在弟1bit，(0,2)和(1,3)在弟2bit，(0,1),(1,2)和(2,3)在第3个bit,(0,0)在第4个bit，(1,0)在第5个bit
//        if (visited[BAK] & ((row-col+n)<<1)) return false;

        if (chkBit(visited[ROW], row)) return false;
        if (chkBit(visited[COL], col)) return false;
        // 对于/的情况，某个bit等于x+y+1的值, 例如: (0,0)在第1bit，(1,0)和(0,1)在第2bit，(0,2),(1,1)和(2,0)在弟3个bit，总共2*n-1
        if (chkBit(visited[SLA], row+col)) return false;
        // 对于\的情况，某个bit等于x-y+n的值, 例如：(0,3)在弟1bit，(0,2)和(1,3)在弟2bit，(0,1),(1,2)和(2,3)在第3个bit,(0,0)在第4个bit，(1,0)在第5个bit
        if (chkBit(visited[BAK], row-col+n-1)) return false;
        return true;
    }
    
    void setValid(vector<int> &visited, vector<string> &path, int i, int n) {
        int row = path.size(), col = i;
        string line = string(n,'.');
        // path.push_back(line[col]='o'); 大意啦
        // line[col]='o';// 尼玛，看成o了
        line[col]='Q';
        path.push_back(line);
        
//        visited[ROW] |= ((row+1)<<1);
//        visited[COL] |= ((col+1)<<1);
//        visited[SLA] |= ((row+col+1)<<1);
//        visited[BAK] |= ((row-col+n)<<1);
        setBit(visited[ROW], row);
        setBit(visited[COL], col);
        setBit(visited[SLA], row+col);
        setBit(visited[BAK], row-col+n-1);
    }
    void resetValid(vector<int> &visited, vector<string> &path, int i, int n) {
//        int row = path.size(), col = i; 注意index，这样做的话row需要减1
        path.pop_back();
        int row = path.size(), col = i;
        
//        visited[ROW] &= ~((row+1)<<1);
//        visited[COL] &= ~((col+1)<<1);
//        visited[SLA] &= ~((row+col+1)<<1);
//        visited[BAK] &= ~((row-col+n)<<1);
        clkBit(visited[ROW], row);
        clkBit(visited[COL], col);
        clkBit(visited[SLA], row+col);
        clkBit(visited[BAK], row-col+n-1);
    }
};

ostream & operator<< (ostream &os, vector<vector<string>> &rtn) {
    os << "[";
    
    for (int i = 0; i < rtn.size(); ++i) {
        int size = rtn[i].size();
        os << "[";
        for (int j = 0; j < size; ++j) {
            os << rtn[i][j] << ((j+1 == size)?"":",");
        }
        os << "]" << ((i+1 == rtn.size())?"":",");
    }
    
    os << "]";
    return os;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    Solution gua;
    int n;
    vector<vector<string>> rtn;
    rtn = gua.solveNQueens(n = 4);
    cout << rtn << endl;
    
    return 0;
}


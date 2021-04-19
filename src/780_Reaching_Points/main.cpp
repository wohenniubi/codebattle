
#include <iostream>
#include <unordered_map>
#include <memory>

using namespace std;

struct myHash {
    size_t operator() (const pair<int,int> &A) const {
        return std::hash<int>()(A.first) ^ std::hash<int>()(A.second);
    }
};

class Solution {
public:
    // 方法2:充分观察到规则和数据特点，数据是正整数，所以如果tx>ty，那么(tx,ty)这个点必然是从(tx-ty, ty)演进过来
    // 而如果tx-ty依旧大于ty，那么只能是从(tx-2ty,ty)演进过来的，现在是不是有一些想法了；
    // 然后从target到src，因为取mod用减号好，然后先用递归写一个
    bool reachingPoints(int sx, int sy, int tx, int ty) {
        // 返回条件
        if (sx > tx || sy > ty)
            return false;//一旦小于某个值就不可能翻盘了
        
        if (sx == tx)// 此时只可能变换y值了
            return (ty - sy)%tx == 0;//reachingPoints(sx, sy, tx, ty-tx);
        if (sy == ty)// 此时只可能变换x值了
            return (tx - sx)%ty == 0;//reachingPoints(sx, sy, tx-ty, ty);
        
        if (tx > ty)
            return reachingPoints(sx, sy, tx%ty, ty); // 这样再优化一下
            //return reachingPoints(sx, sy, tx-ty, ty);
        if (tx < ty)
            return reachingPoints(sx, sy, tx, ty%tx); // 这样再优化一下
            //return reachingPoints(sx, sy, tx, ty-tx);
        
        // assert(0);//在本题里面应该是不可能的，因为都是正整数，正整数不可能出现x+y =y或者x = x+y的情况
        return false;
    }

    bool reachingPoints1(int sx, int sy, int tx, int ty) {
        // 方法1，DFS，我估计会超时，挂在sx = 35, sy = 13, tx = 455955547, ty = 420098884
        // 因为感觉是二叉树遍历，防止重复访问；然后由于数据量大，弄到堆上面；然后又fancy了一下smart pointer
        // unordered_map<pair<int,int>,bool,myHash> *memo = new unordered_map<pair<int,int>,bool,myHash>;
        unique_ptr<unordered_map<pair<int,int>,bool,myHash>> memo(new unordered_map<pair<int,int>,bool,myHash>);
        
        return dfs(sx, sy, tx, ty, *memo);
        //*memo传入的是unique_ptr里面的new结构的reference；memo.get()获得的是new结构的pointer，因此dfs那里要对应写成*
    }
    
    bool dfs (int sx, int sy, int tx, int ty, unordered_map<pair<int,int>,bool,myHash> &memo) {
        // 返回条件
        if (sx > tx || sy > ty) // 根据题目的设定，这种情况下没有可能到达target
            return false;
        else if (sx == tx && sy == ty)
            return true;
        
        auto iter = memo.find({sx, sy});
        if (end(memo) != iter)
            return iter->second;
        
        // 开始处理两个子节点
        if (!dfs(sx+sy, sy, tx, ty, memo) && !dfs(sx, sx+sy, tx, ty, memo)) {
            memo[{sx, sy}] = false;
            return false;
        } else {
            memo[{sx, sy}] = true;
            return true;
        }
    }
};

int main(int argc, const char * argv[]) {
    Solution gua;
    bool rtn;
    int sx, sy, tx, ty;
    rtn = gua.reachingPoints(sx = 35, sy = 13, tx = 455955547, ty = 420098884);
    cout << "expect value = 0, actual value = " << rtn << endl;

    rtn = gua.reachingPoints(sx = 1, sy = 1, tx = 3, ty = 5);
    cout << "expect value = 1, actual value = " << rtn << endl;
    
    rtn = gua.reachingPoints(sx = 1, sy = 1, tx = 2, ty = 2);
    cout << "expect value = 0, actual value = " << rtn << endl;
    
    return 0;
}

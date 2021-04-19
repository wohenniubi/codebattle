
#include <vector>
#include <set>
#include <unordered_map>
#include <iostream>

using namespace std;

class ExamRoom {
public:
    struct MyCmp {
        bool operator()(vector<int> &A, vector<int> &B) {
            int lenA = A[1] - A[0] - 1;
            int lenB = B[1] - B[0] - 1;
            if (lenA == lenB)
                return A[0] > B[0];// 按照起点降序排列，这样取最大的时候才可以取到起点较小的间隔
            else
                return lenA < lenB;// 按照len升序排列
        }
    };
    
    #define MYITER multiset<vector<int>, MyCmp>::iterator
    // multimap<int, vector<int>, MyCmp> intervals;// 这个间隔左右两边的index都坐着人
    multiset<vector<int>, MyCmp> intervals;// 没必要保存长度，因为长度可以从MyCmp里面体现
    
    // 由于间隔一定不会重叠，所以可以统一用左边界代表间隔的key值，因此可以简化数据结构
    unordered_map<int, MYITER> startmap;// 以某个index作为起点的间隔
    unordered_map<int, MYITER> endmap;// 以某个index作为终点的间隔
    int N; // 还得存下来才行
    
    void addInterval(pair<int,int> interval) {
        auto & [bgn, end] = interval;
        int len = bgn - end -1;
//        auto iter = intervals.emplace({len,{bgn,end}}); 别大意啊，emplace
//        auto iter = intervals.begin();
        auto iter = intervals.emplace(make_pair(vector<int>{bgn,end},vector<int>));// 直接使用{}会编译失败，因为编译器不知道该用什么类型
        startmap[bgn] = iter;
        endmap[end] = iter;
    }
    
    void delInterval(MYITER iter) {
        //auto [bgn, end] = iter->second; 为啥这样不得行??
        int bgn = (*iter)[0], end = (*iter)[1];
        startmap.erase(bgn);
        endmap.erase(bgn);
        
        startmap.erase(end);
        endmap.erase(end);
    }
    
    ExamRoom(int N) {
        //系统设计第一步，先交流，沟通获取信息，整理为：系统规模，用户行为，测试用例和接口
        
        //系统设计第二步，将用户行为确定为数据结构，需要哪些才能支持全部或部分的操作
        //      - 本题的行为之一：插入一个人，找最远，那就是取最长线段的中点    —— 暗示需要BST
        //      - 本题的行为之二：去掉一个人，释放座位，并且恢复数据结构       —— 暗示需要哈希表
        //      - 本题的行为之三：多次操作，不可能每次都遍历
//        multimap<int, vector<int>, MyCmp> intervals;// 这个间隔左右两边的index都坐着人
//
//        // 由于间隔一定不会重叠，所以可以统一用左边界代表间隔的key值，因此可以简化数据结构
//        unordered_map<int, MYITER> startmap;// 以某个index作为起点的间隔
//        unordered_map<int, MYITER> endmap;// 以某个index作为终点的间隔
        
        addInterval({-1, N});
        // 这是一个虚拟的间隔，因为释放座位时index不会等于-1或者N
        // 所以不需要在哈希表中保留这个间隔的信息
    }
    
    int seat() {
        auto iter = prev(intervals.end());//获得最大的一个interval
        //auto [bgn, end] = iter->second; 为啥这样不得行??
        int bgn = (*iter)[0], end = (*iter)[1];
        int rtn = -1;
        if (1 == end - bgn) return rtn; //座位满了
        
        if (-1 == bgn) {
            rtn = 0; // 有个最大的间隔，左边还没人坐，再根据题意，先取小的
        } else if (N == end) {
            rtn = N-1; // 有个最大的间隔，最右边没人坐，根据题意，离得最远
        } else {
            rtn = bgn + (end - bgn)/2; // 现在就是取平均了
        }
        
        // 座位搞定之后，要维护数据结构，拆分
        delInterval(iter);// 去掉旧间隔
        addInterval({bgn, rtn});// 加入左半新间隔
        addInterval({rtn, end});// 加入右半旧间隔
        return rtn;
    }
    
    void leave(int p) {
        // 要释放座位啦
        if (!startmap.count(p) || !endmap.count(p)) return;
        
        // 问题来了，因为要合并两个间隔，即查找到两个间隔然后删掉，如果仅仅只保存了以p为起点的间隔
        // 那么找不到以p为终点的间隔，所以还是需要endmap
        auto bgniter = startmap[p];
        auto enditer = endmap[p];
        int bgn = (*enditer)[0];
        int end = (*bgniter)[1];
        
        // 因为必定不会移除-1和N，所以不会担心重复删除同一个iter的情况
        delInterval(bgniter);// 去掉旧间隔
        delInterval(enditer);// 去掉旧间隔
        addInterval({bgn, end});
    }
};


int main() {
  int N;
  ExamRoom gua(N=10);
  
  cout << "expect value = 0, actual value = " << gua.seat() << endl;
  cout << "expect value = 9, actual value = " << gua.seat() << endl;
  cout << "expect value = 4, actual value = " << gua.seat() << endl;
  cout << "expect value = 2, actual value = " << gua.seat() << endl;
  gua.leave(4);
  cout << "expect value = 5, actual value = " << gua.seat() << endl;

  return 0;
}


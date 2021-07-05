
#include <iostream>
#include <map>

using namespace std;

class RangeModule {
public:
    map<int,int> memo;// key是起始位置，value是结束位置；充分利用红黑树的排序性质
    
    //Runtime: 192 ms, faster than 63.39%
    //Memory Usage: 71.7 MB, less than 34.44%
    RangeModule() {
        // interval问题，但是根据本题的要求，其实并不需要保存多余（重叠）的间隔，
        // 因为有交叠的间隔会相互融合，故只要找到起始位置较小的间隔，然后
        // 修改结束位置为最大值就好了，故不需要提供自定义的二维比较函数
        memo.clear();
    }
    
    void addRange(int left, int right) {
        // 插入时就要找到第一个重复的间隔，这可能是需要插入的新间隔[left,Y)，
        // 也可能是小于等于left、但是可以与[left,right)重合的间隔
        // 因此操作是利用lower_bound
        auto lhs = memo.lower_bound(left);
        auto rhs = memo.upper_bound(right);// 这里确保rhs是与right完全不重合的
        
        if (lhs != memo.begin()) {
            //[3,4), [5,7)，添加[4,5)会把整个区间连接起来
            if ((--lhs)->second >= left) {
                ;// 说明左侧的间隔也可以重叠，所以lhs已经往左侧挪动一位,
            } else {
                ++lhs;// 把lhs恢复
            }
        }
        // 好啦，现在开始删除lhs到rhs之间的所有间隔
        if (lhs == rhs) {
            // 表明没有重叠的间隔，那么直接添加
            memo[left] = right;
        } else {
            // 现在要删除lhs和rhs之间的所有间隔，不过删之前需要获得最左边和最右边的值
            int newlhs = min(left, lhs->first);
            int newrhs = max(right, (--rhs)->second);
            memo.erase(lhs, (++rhs));//删除时也是左闭右开，要恢复rhs
            memo[newlhs] = newrhs;
        }
    }
    
    bool queryRange(int left, int right) {
        // 存在[3,7),查询[4,5)
        auto lhs = memo.lower_bound(left);
        auto rhs = memo.upper_bound(right);// 这里确保rhs是与right完全不重合的
        
        if (lhs != memo.begin()) {
            // 要判断一下lhs的前一个间隔是否与left有交集，对lhs进行适当的修正
            if ((--lhs)->second <= left) {
                ++lhs;// 小于等于都表示没有交集(题目规定，相等也表示不重合)，需要恢复lhs
            }// 大于left，会对修正后的lhs进行深入判定
        }
        
        if (lhs == rhs) {
            return false;// 修正完了之后还是空区间，返回false
        } else {
            return (lhs->first <= left) && (lhs->second >= right);
        }
    }
    
    void removeRange(int left, int right) {
        // 存在[3,7),删除[4,5)
        auto lhs = memo.lower_bound(left);
        auto rhs = memo.upper_bound(right);// 这里确保rhs是与right完全不重合的
        
        if (lhs != memo.begin()) {
            // --lhs的first必定是小于等于left的，因此要判断重叠只需要判断右边界second
            if ((--lhs)->second > left) {
                ;// 此时的lhs已经完成了向左的移动，妥了
            } else {
                ++lhs;// 此时lhs代表的间隔右边界与left完全不重合(相等也是不重合)，因此要恢复
            }
        }
        if (lhs == rhs) return;// 没什么可以删除的，结束操作
        // 现在开始删除操作
        int newrhs = (--rhs)->second;// [right, newrhs)会成为新的间隔
        int newlhs = lhs->first;// [newlhs, left]会成为新的间隔
        memo.erase(lhs, (++rhs));// 先删除[lhs, rhs)之间的所有间隔，然后再添加两个新的间隔
        memo[newlhs] = left;
        memo[right] = newrhs;
    }
};

/**
 * Your RangeModule object will be instantiated and called as such:
 * RangeModule* obj = new RangeModule();
 * obj->addRange(left,right);
 * bool param_2 = obj->queryRange(left,right);
 * obj->removeRange(left,right);
 */

int main(int argc, const char * argv[]) {
    RangeModule gua;
    gua.addRange(10, 20);
    gua.removeRange(14, 16);
    
    cout << "expect value = 1, actual value = " << gua.queryRange(10, 14) << endl;
    cout << "expect value = 0, actual value = " << gua.queryRange(13, 15) << endl;
    cout << "expect value = 1, actual value = " << gua.queryRange(16, 17) << endl;
    return 0;
}

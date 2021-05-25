
#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
public:
    //Runtime: 0 ms, faster than 100.00%
    //Memory Usage: 7.4 MB, less than 35.90%
    bool circularArrayLoop(vector<int>& nums) {
        int n = nums.size();
        vector<int> visit(n);
        
        for (int i = 0; i < n; ++i) {
            if (visit[i]) continue;
            
            // 从nums[i]开始操作;
            // 注意还要使用一个哈希表，因为仅仅根据visit，只能说明被访问过；而某个没有被访问的节点也可以跳转到访问过的节点，故不能贸然认为visit=1就是环
            unordered_set<int> memo;// 这里记录从nums[i]开始，被访问过的所有节点，一旦本次出现重复，那就是环
            int curr = i;
            while (true) {
                visit[curr] = 1;
                memo.insert(curr);
                
                int next = ((curr + nums[curr])%n + n)%n; //这样一定是在[0,n-1]
                if (nums[curr] * nums[next] < 0 || curr == next)
                    break;// 如果数据正负不同或者是自循环的点，结束操作
                
                if (memo.count(next))
                    return true;// 说明在以nums[i]为开始的序列里面找到了环
                curr = next;// 保证循环继续进行
            }
        }
        return false;// 跳出循环说明没有找到环
    }
    
    // 下面的方法思路正确，但是还缺少一些步骤，所以不正确
    bool circularArrayLoop1(vector<int>& nums) {
        // 看题目的意思就就是vector树的感觉，再配合BFS+DFS查找环，来吧
        int size = nums.size();
        // 这个visit数组后续可以优化，因为题目有个很重要的信息nums[i] != 0，那么就可以设置为0，表示访问过
        vector<int> visit(size);
        
        // 这个for loop就是BFS+DFS在vector树里面查找环
        for (int i = 0; i < size; ++i) {
            if (visit[i]) continue;
            // 对于先前DFS已经访问过的节点，即然还可以执行到这里，说明没有找到环（默认找到环之后会return true），那也不用重复操作了
            
            // 现在从nums[i]开始DFS
            int next = i, cnt = 0, isValid = 1;
            while (visit[next] == 0) {
                visit[next] = 1;
                ++cnt;
                int cur = next;
                next = ((next+nums[next])%size+size)%size;//获得新的index，同时注意循环，这取模适用于正数和负数
                
                // 这里还要保证同正同负，且要避开长度为1的环，也即是自循环
                if (nums[cur] * nums[next] < 0 || cur == next) {
                    isValid = 0;
                    break;
                }
            }
            // 跳出while循环说明可能找到环了，环肯定是首尾相同
            // if (next == i && cnt > 1) 无法应对[1,1,2]的情况
            if (isValid && cnt > 1)
                return true;// 只有两个数不等，才能说明是长度大于1的环；否则继续执行吧
        }
        return false;
    }
};

int main(int argc, const char * argv[]) {
    Solution gua;
    bool rtn;
    vector<int> nums;
    
    rtn = gua.circularArrayLoop(nums = {-1,1});
    cout << "expect value = 0, actual value = " << rtn << endl;

    rtn = gua.circularArrayLoop(nums = {-1,2});
    cout << "expect value = 0, actual value = " << rtn << endl;

    rtn = gua.circularArrayLoop(nums = {2,2,2,2,2,4,7});
    cout << "expect value = 0, actual value = " << rtn << endl;

    rtn = gua.circularArrayLoop(nums = {-1,1,2});
    cout << "expect value = 1, actual value = " << rtn << endl;

    rtn = gua.circularArrayLoop(nums = {2,-1,1,2,2});
    cout << "expect value = 1, actual value = " << rtn << endl;
    return 0;
}

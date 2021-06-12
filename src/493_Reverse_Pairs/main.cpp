
#include <iostream>
#include <unordered_map>
#include <vector>
#include <map>

using namespace std;

class Solution {
public:
    // 这个update固定只对某个值+1，因此省略了val
    void update(int pos, vector<int> &bit) {
        for (int i = pos; i < bit.size(); i+= (i&-i)) {
            ++bit[i];
        }
    }
    // 这个update获得bit[0,pos]之间的sum
    int getSum(int pos, vector<int> &bit) {
        int rtn = 0;
        //for (int i = pos; i >= 0; i-=(i&-1)) { // 非常玄妙，i>=0会到值死循环，因为传入的pos可以为0
        for (int i = pos; i > 0; i-=(i&-i)) {
            rtn += bit[i];
        }
        return rtn;
    }
    
    //Runtime: 224 ms, faster than 74.69%
    //Memory Usage: 60.6 MB, less than 57.65%
    int reversePairs(vector<int>& nums) {
        // 试着另一种做法BIT，不过要花很多内存
        vector<int> n = nums;// 这是对原数据的备份，因为要sort
        sort(begin(n), end(n));// [1,3,2,3,1] -> [1,1,2,3,3]
        
        unordered_map<int,int> dict;
        for (int i = 0; i < nums.size(); ++i)
            dict[n[i]] = i+1;// 总是以最后出现的那个pos作为n[i]的位置，然后index有+1的关系
        
        vector<int> bit(nums.size()+1);
        // 本题中BIT数组的getSum返回的是满足nums[i]>nums[j]/2.0条件的那些数的个数
        // 满足条件的这些数据在排序之后的n数组中可以通过lower_bound轻松获得，至于他们是否出现，借助了BIT数组；
        // 后者采用分散存储，每次更新时仅部分更新，getSum也仅需O(logn)就可以返回；而且由于BIT是不断填充的，
        // 即使在遍历nums时出现了某个相同的值，其前后两次getSum获得的个数也不相同，是不是非常fancy！！
        
        // 现在开始更新bit，从右往左遍历，这样可以满足reverse pair的i<j的关系
        // 然后每次加入一个nums[i]时，找到n数组中、以nums[i]/2.0作为lower_bound的位置
        // 这样[0, lower_bound)的这些数就是满足reverse pair条件的数了，可以统计个数
        int rtn = 0;
        for (int i = nums.size()-1; i >= 0; --i) {
            // 这种方式其实是将每个新加入的数在BIT数组中进行了记录，还附带了分类，适用于流操作
            int pos = lower_bound(begin(n), end(n), nums[i]/2.0) - begin(n);
            rtn += getSum(pos, bit);
            update(dict[nums[i]], bit);
        }
        return rtn;
    }
    
    // 非常犀利的做法，改写mergeSort，精妙的解决问题
    //Runtime: 312 ms, faster than 59.71%
    //Memory Usage: 44.9 MB, less than 99.56%
    int reversePairs1(vector<int>& nums) {
        return mergeSort(nums, 0, nums.size()-1);
    }

    int mergeSort(vector<int> &nums, int lhs, int rhs) {
        //返回条件：根据题意，bgn等于end时不会再有pair，所以直接返回
        if (lhs >= rhs)
            return 0;
        
        int mid = lhs + (rhs - lhs)/2;
        int lval = mergeSort(nums, lhs, mid);
        int rval = mergeSort(nums, mid+1, rhs);
        
        // 现在开始两个sorted序列的merge，也就是后序遍历嘛
        int rtn = 0;
        for (int i = lhs, j = mid+1; i <= mid; ++i) {
            while (j <= rhs && nums[i]/2.0 > nums[j]) {
                ++j;
            }
            // 跳出while循环说明nums[i]不大于2*nums[j]了
            // 那么因为右边是排了序的，后面都不用检查了；此时以nums[i]为左边的pair的对数就是j移动的个数
            // 也不需要把j恢复到mid+1，因为左边也是排了序的，nums[i+1]必定可以与nums[i]构成pair的那些右边组成pair
            rtn += (j - (mid+1));
        }
        // 别忘记还要对左右边的subarray进行merge，非常精妙的一句
        sort(nums.begin()+lhs, nums.begin()+rhs+1);
        
        return rtn + lval + rval;
    }
};


int main(int argc, const char * argv[]) {
    Solution gua;
    int rtn;
    vector<int> nums;
    
//    rtn = gua.reversePairs(nums = {2000000003,236,2000000007,237,2000000002,2000000005,233,233,233,233,233,2000000004});
    rtn = gua.reversePairs(nums = {2000000003,236,2000000007,237,2000000002,233});
    cout << "expect value = 6, actual value = " << rtn << endl;
    
    rtn = gua.reversePairs(nums = {1,3,2,3,1});
    cout << "expect value = 2, actual value = " << rtn << endl;

    rtn = gua.reversePairs(nums = {2,4,3,5,1});
    cout << "expect value = 3, actual value = " << rtn << endl;
    return 0;
}
    

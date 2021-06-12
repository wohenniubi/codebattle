
#include <iostream>
#include <vector>

using namespace std;

class NumArray {
public:
    vector<int> onums;// 因为update时需要用到diff，如果不保存旧的data，就不方便计算diff
    vector<int> cache;// cache保存的是分段sum的中间结果，如果要计算[0,i]这个段到sum，还需要操作一下
    
    //Runtime: 384 ms, faster than 68.17% 
    //Memory Usage: 150.7 MB, less than 71.06%
    // 复习一下binary indexed tree，也就是(i&-i)的技巧
    NumArray(vector<int>& nums) {
        onums = nums;
        int n = nums.size();
        
        // 现在开始构建BIT
        cache.resize(n+1);
        //cache.insert(end(cache), begin(nums), end(nums));
        
        for (int i = 0; i < n; ++i) {
            int diff = nums[i];
            
            for (int j = i+1; j <= n; j += (j&-j)) {
                cache[j] += diff;
            }
        }
    }
    
    void update(int index, int val) {
        int diff = val - onums[index];
        
        // 累加时要用chache的索引j，它满足binary index关系，可以不用转换
        //for (int j = index+1; j <= cache.size(); j+=(j&-j)) { // 大意了，再怎样也不能越界呀
        for (int j = index+1; j < cache.size(); j+=(j&-j)) {
            cache[j] += diff;
        }
        // 大意了啊大意啊！！！别忘了更新onums的值
        onums[index] = val;
    }
    
    // 返回[0, index]之间的Sum
    int sumSingle(int index) {
        // 虽然从index到cache的索引有+1的关系，但是cache的Sum有可能仅仅是中间结果，因此需要累加
        int rtn = 0;
        //for (int j = index+1; j > 0; j -= (j&-j)) {
        // 大意了，由于sumSingle的入参index是non-inclusive的，因此相当于转换到了cache的index，不能重复再加1
        for (int j = index; j > 0; j -= (j&-j)) {
            rtn += cache[j];// 看cache这个index里包含了多少个bit-1
        }
        return rtn;
    }
    
    int sumRange(int left, int right) {
        // 通过获得[0,left)和[0, right+1)，然后相减得到[left,right+1]区间内的数据之和
        // 这里只要再多定义一个函数，并且修改一下输入，则可以复用这个函数
        return sumSingle(right+1) - sumSingle(left);
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * obj->update(index,val);
 * int param_2 = obj->sumRange(left,right);
 */

int main(int argc, const char * argv[]) {
    vector<int> nums;
    NumArray gua(nums = {1,3,5});
    
    cout << "sumRange(0,2) = " << gua.sumRange(0, 2) << endl;
    gua.update(1,2);
    cout << "sumRange(0,2) = " << gua.sumRange(0, 2) << endl;
    return 0;
}

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    // leetcode的讨论, 思路清晰, 操作简单, 就学这种了
    // https://leetcode.com/problems/median-of-two-sorted-arrays/discuss/2471/very-concise-ologminmn-iterative-solution-with-detailed-explanation
    // 思路都清楚了, 就是进行二分查找, 而且是以短的数组进行分割, 因为两个数组的一半是固定的, 
    // 所以长短数组是关联的, 即短数组的分割一旦清楚了, 长数组的分割也就清楚了; 难点是具体操作
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size(), n = nums2.size();
        // 以下简单操作, 完成两个数组的交换, 是不是很惊艳, 或者用nums1.swap(nums2)
        if (m > n) return findMedianSortedArrays(nums2, nums1);
        
        // 现在m总是小于n的啦, 咱们开始对短的数组nums1进行分割吧
        // 不过为了后续计算index时不受奇偶影响, 这里小trick是假定原始数据之间填充有一些虚拟的位置#,
        // 分割就落在这些虚拟的位置以及原始的数据之上, e.g 原始数据长度为N, 填充后长度为2N+1, 
        // 或者说, 位于分割左边的原始数据和填充的虚拟数据的个数为0~2N, 这也就是二分的区间
        int lhs = 0, rhs = 2*m;
        while (lhs <= rhs) {// 这里为啥使用=, 后面再看
            int midm = lhs + (rhs - lhs)/2;// 注意这里midm的意义是个数, 不是index
            // 计算另一个长数组中分割左侧的数据个数, 由于分割左侧的总数据为m+n, 所以容易算出来
            int midn = m + n - midm;
            
            // 然后计算四个位置的index, 得到四个数, 比较之后才好指导midm该如何进行调整
            // 这里需要根据长度获得index, 映射关系是A[(len-1)/2], A[len/2], 这其实就是median的两个值
            // int mLval = nums1[(midm-1)/2];
            // int mRval = nums1[midm/2];
            // int nLval = nums2[(midn-1)/2];
            // int nRval = nums2[midn/2];
            // 
            // 然后注意到上面的数据可能出现越界, 例如: midm等于0时midm-1越界, 为了考虑这些exception
            // 理解这些情况的意义, 例如: midm = 0, 表明短数组没有贡献数据, 不可能再出现贡献多了(继续减少midm)这种情况,
            // 即 mLval>nRval这个分支是绝不会发生的, 那么把mLval(左侧数据)设置为INT_MIN就可以完美解决这个问题
            // 同理对于midm = 2m, 表明短数组已经贡献了所有, 不可能再出现贡献少了(继续增加midm)这种情况
            // 即 nLval>mRval 这个分支是绝对不会发生的, 那么把mRval(右侧数据)设置为INT_MAX就可以完美解决该问题
            // 类似的对于midn = 0, 这可以发生在m和n相等, 且midm等于2*m时, 此时长数组没有贡献数据, 不可能再贡献多了(继续减少midn),
            // 所以 nLval>mRval 这个分支不会发生, 那么把nLval(左侧数据)设置为INT_MIN就可以了
            // 同理对于 midn = 2*n, 这可以发生在m和n相等, 且midm等于0时, 此时长数组贡献所有数据, 不可能再贡献少了(继续增大midn),
            // 所以 mLval > nRval 这个分支不会发生, 那么把nRval(右侧数据)设置为INT_MAX就可以了
            int mLval = (midm==0)? INT_MIN: nums1[(midm-1)/2];
            int mRval = (midm==2*m)? INT_MAX: nums1[midm/2];
            int nLval = (midn==0)? INT_MIN: nums2[(midn-1)/2];
            int nRval = (midn==2*n)? INT_MAX: nums2[midn/2];
            
            if (mLval > nRval) {
                rhs = midm-1;// 说明短数组贡献多了, 长了, 那么midm需要减小, 短数组的上界减小
            } else if (nLval > mRval) {
                lhs = midm+1;// 说明长数组贡献多了, 长了, 那么midm需要增大, 短数组的下界增大
            } else {
                // 这个分支用于处理刚好满足mLval < nRval, nLval < mRval的情况
                // 此时短数组和长数组的划分就是median的分界线, 只不过现在有四个数, 需要考虑使用
                // 哪两个来计算median, 想到: 由于会被排序, 此时左边两个数(右边两个数)只会取1个,
                // 而且左边的数位于median左边, 故必定比右边的数小
                // 因此左边的两个数要取最大的, 右边的两个数取最小的, 否则排序上就矛盾了
                return (max(mLval, nLval) + min(mRval, nRval))/2.0;// 注意用2.0而不是2
            }
        }// 跳出while循环时给个返回值吧
        return 0.0;
    }
};

int main() {
    // vector<int> nums1 = {1,3,6,8,10,32};
    // vector<int> nums2 = {2,4,5,7};
    vector<int> nums1 = {2,3};
    vector<int> nums2 = {1};
    double rtn;
    Solution gua;
    rtn = gua.findMedianSortedArrays(nums1, nums2);
    cout << "expect value = 2, actual value = " << rtn << endl;

    return 0;
}


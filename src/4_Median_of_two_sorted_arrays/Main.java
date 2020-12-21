class Solution {
    // Runtime: 2 ms, faster than 99.67% 
    // Memory Usage: 39.8 MB, less than 96.74%
    public double findMedianSortedArrays(int[] nums1, int[] nums2) {
        int len1 = nums1.length, len2 = nums2.length;
        final int INT_MAX = 1000007;// 尼玛java不能自动把double转为int嗦，1e7;//2,147,483,647
        final int INT_MIN = -INT_MAX;
        if (len1 > len2) return findMedianSortedArrays(nums2, nums1);
        
        // 沿用二分查找的思路，要找到median，其实就是要将两个sorted array各自拆分为左右两个部分
        // 然后保证两个sorted array的左边部分的最大值小于两个右边部分的最小值；即如下形状：
        // 0 ... m1L, m1R, ...m-1
        // 0 ... n1L, n1R, ...n-1
        // 其中m1L要小于n1R，n1L要小于m1R；m1L和n1L，或者m1R和n1R的大小可以不确定
        // 然后就是将这个m1L与mid建立关系了，注意还隐含了其他关系，例如m1L和n1L，他们受到median，即(m+n)/2的控制
        
        // 在具体运算时，又在以上认知的基础上加入了一个小trick，即默认在array里面插入了#，即:1,2 -> #1,#,2,#
        // 这样可以很容易的得到切割位置对应的原始array中的值
        int lhs = 0, rhs = 2*len1; // 这里插入#之后总长度变为2*len1 +1，index只能是0~2*len1
        while (lhs <= rhs) {
            int mid = lhs + (rhs - lhs)/2;
            // 从这个切割位置mid可以得到len1序列的左边最大值和右边最小值，即nums1[m1L]和nums1[m1R]
            // #1#2#, mid = 0或者1时，把1切到左半，那么num1L=nums1[0]=1；对于边界mid=0时需要边界保护，边界的值设置为方便后续处理的值
            int num1L = (mid == 0) ? INT_MIN: nums1[(mid-1)/2];
            int num1R = (mid == 2*len1) ? INT_MAX: nums1[mid/2];
            
            // 同时基于隐含条件，m1L和n1L受到median的控制，所以可以得到nums2里面的切割位置index
            int mid2 = len1+len2 - mid;
            // 因为median，所以两部分加起来的个数占去了2*len1+1和2*len2+1的一半，即：len1+len2+1，
            // 再由于mid2是切割位置即index，则由长度转为index时要去掉1，得到：len1+len2-mid 
            // 然后操作与上面类似，也需要进行边界保护
            int num2L = (mid2 == 0)? INT_MIN: nums2[(mid2-1)/2];
            int num2R = (mid2 == 2*len2)? INT_MAX: nums2[mid2/2]; // 比如len1=len2，mid=0
            
            // 终于开始根据数据进行折半查找了; 此时就知道上面边界的值为什么要设置为INT_MIN和INT_MAX了
            // 切记切记，都是以左半部分进行比较
            // if (num1R > num2L) { 大意大意呀！！！本来就应该是num1R > num2L
            if (num1L > num2R) {
                // 这是3 || 4,   1 | 2的情况，||对应mid的切割线，|对应受到(m+n)/2控制的len2中的切割线
                rhs = mid-1;// 说明len1贡献多了，把||切割线向左边压
            // } else if (num2R < num1L) { 大意啦大意啦
            } else if (num2L > num1R) {
                // 这是1 || 2,   3 | 4的情况，// 说明len1贡献少了，把||切割线向右边压
                lhs = mid+1;
                // 一般来讲，因为循环条件是lhs <= rhs, 所以这里应该是lhs = mid，但是由于没有想过要跳出循环，
                // 所以最终不会用跳出循环的那个lhs（即rhs +1）来进行处理。因此这里直接是mid+1，因为mid并不满足切割要求
            } else {
                // 这种情况下满足切割情况，需要把两个array左边部分的最大值和右边部分的最小值找出来
                // 此时知道为什么要把左边部分越界设置为INT_MIN，右边越界设置为INT_MAX了，因为不会对max和min造成影响
                return (Math.max(num1L, num2L) + Math.min(num1R, num2R))/2.0;
            }
        }
        return 0.0;//代码完整一点，设置一个返回值，应该不会到这里；如果两个array都为空的话，建议在输入时进行判断
    }
}

public class Main {
  public static void main(String[] args) {
    Solution gua = new Solution();
    double rtn;

    int [] nums1 = {1,3};
    int [] nums2 = {2};
    rtn = gua.findMedianSortedArrays(nums1, nums2);
    System.out.println("expect value = 2.0, actual value = " +rtn);
    
    nums1 = new int[]{1, 3}; 
    nums2 = new int[]{2, 4}; 
    rtn = gua.findMedianSortedArrays(nums1, nums2);
    System.out.println("expect value = 2.5, actual value = " +rtn);
   
    nums1 = new int[]{}; 
    nums2 = new int[]{1}; 
    rtn = gua.findMedianSortedArrays(nums1, nums2);
    System.out.println("expect value = 1.0, actual value = " +rtn);
  }
}



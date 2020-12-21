
class Solution {
    //Runtime: 35 ms, faster than 83.54%
    //Memory Usage: 60.8 MB, less than 5.49%
    public double findMaxAverage(int[] nums, int k) {
        final double miu = 0.000001;
        int len = nums.length;
        // int [] sums = new int[len+1];
        double [] sums = new double[len+1];
        
        // 最大平均值必定是在最小值和最大值之间
        double lhs = nums[0], rhs = nums[0];
        for (int i = 1; i < len; ++i) {
            if (nums[i] < lhs) lhs = nums[i];
            if (nums[i] > rhs) rhs = nums[i];
        }
        
        // 来吧，开始夹逼得到最大平均值吧
        while (lhs + miu < rhs) {
            double mid = lhs + (rhs - lhs)/2;
            double minSum = 0;// 初始化为0可以吗？需不需要设置为最大？
            // 因为与平均数相减之后，仅有构成最大平均数的数组差值和为0，其他都应该小于0；
            // 而一旦找到这个大于0的差值和，就意味着可以结束当前loop，所以本题很特殊，初始化为0就可以了
            int check = 0;
            
            // 计算差值和数组，并在其中找到一个0到i-k-1之间包含最小差值和的sums
            // 这个sums因为是和，因此被sums[i]减去之后就可以得到长度为>=k的、具有最大的差值和的子数组
            for (int i = 1; i <= len; ++i) {
                sums[i] = sums[i-1] + (nums[i-1] - mid);
                
                // 顺手就把最小差值和找到了，sums[i'-k]保存的是[0,i'-k)的子数组的差值和
                // sums[i]减去sums[i'-k]，得到的就是i'-k到i-1的子数组，其长度为i-i'+k，满足大于等于k的条件
                if (i >= k) {
                    // minSum = (sums[i-k] < minSum)? sums[i-k]): minSum;
                    //if (sums[i-k] < minSum) minSum = sums[i-k];
                    minSum = Math.min(sums[i-k], minSum);

                    // 这里跳出会不会太早，是否需要遍历完所有nums再比较? 
                    // 愚以为：由于这是最小，因此一旦构成差值和>0，则不必在计算
                    if (sums[i] > minSum) {
                        check = 1; break;
                    }
                }
            }
            if (check == 1) {
                lhs = mid; //如果存在大于0的差值和数组，说明mid作为最大average的话较小，增大lhs
            } else {
                rhs = mid;
            }
        }
        return lhs;
    }
}

public class Main {
  public static void main(String[] args) {
    Solution gua = new Solution();
    int [] nums = {1,12,-5,-6,50,3};
    int k = 4;
    double rtn;
    rtn = gua.findMaxAverage(nums, k);
    System.out.println("expect value = 12.75, actual value = " + rtn);
  }
}


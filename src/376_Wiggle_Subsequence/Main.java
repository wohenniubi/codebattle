
class Solution {
    //Runtime: 0 ms, faster than 100.00% 
    //Memory Usage: 36.2 MB, less than 16.28%
    public int wiggleMaxLength(int[] nums) {
        int len = nums.length;
        int[] up = new int[len];
        int[] dw = new int[len];
        if (len == 0) return 0;// 有一个例子是[]
        
        int rtn = 1;
        up[0] = 1; dw[0] = 1;
        for (int i = 1; i < len; ++i) {
            if (nums[i] > nums[i-1]) {
                up[i] = Math.max(dw[i-1] + 1, up[i-1]);//或者up长度不变，等价于删除上一个元素
                dw[i] = 1;
            } else if (nums[i] < nums[i-1]) {
                dw[i] = Math.max(up[i-1] + 1, dw[i-1]);
                up[i] = 1;
            } else {
                // 如果进行了空间压缩的话，可以省略这个分支
                dw[i] = dw[i-1];
                up[i] = up[i-1];
            }
        }
        return Math.max(up[len-1], dw[len-1]);
    }
}

public class Main {
  public static void main(String[] args) {
    Solution gua = new Solution();
    int rtn;
    int [] nums = {1, 7, 4, 9, 2, 5};
    rtn = gua.wiggleMaxLength(nums);
    System.out.println("expect value = 6, actual value = " + rtn);
    
    nums = new int[]{1, 17, 5, 10, 13, 15, 10, 5, 16, 8};
    rtn = gua.wiggleMaxLength(nums);
    System.out.println("expect value = 7, actual value = " + rtn);
  }
}



class Solution {
    //Runtime: 1 ms, faster than 95.03%
    //Memory Usage: 38.9 MB, less than 89.94%
    public int singleNumber(int[] nums) {
        int rtn = 0;// 与0异或还是等于自己
        
        for (int i = 0; i < nums.length; ++i) {
            rtn ^= nums[i];
        }
        return rtn;
    }
}

public class Main {
  public static void main(String[] args) {
    Solution gua = new Solution();
    int [] nums;
    int rtn;
    
    nums = new int[]{1};
    rtn = gua.singleNumber(nums);
    System.out.println("expect value = 1, actual value = " + rtn);
    
    nums = new int[]{4,1,2,1,2};
    rtn = gua.singleNumber(nums);
    System.out.println("expect value = 4, actual value = " + rtn);
    
    nums = new int[]{1,2,2};
    rtn = gua.singleNumber(nums);
    System.out.println("expect value = 1, actual value = " + rtn);
  }
}


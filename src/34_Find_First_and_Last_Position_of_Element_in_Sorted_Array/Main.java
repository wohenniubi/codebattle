
class Solution {
    //Runtime: 0 ms, faster than 100.00%
    //Memory Usage: 42.7 MB, less than 5.92%
    // 练习一下二分查找，该函数用于找到大于target的第一个数的pos
    public int binarySearch(int [] nums, int target) {
        if (nums.length == 0) return -1;
        
        int lhs = 0;
        int rhs = nums.length;
        // 找到target的第一个pos，lhs的范围在[0,nums.length]，因此while循环是<，否则可能会越界
        while (lhs < rhs) {
            int mid = lhs + (rhs - lhs)/2;
            if (nums[mid] == target) {
                lhs = mid+1;
            } else if (nums[mid] > target) {
                rhs = mid;
            } else if (nums[mid] < target) {
                lhs = mid+1;
            }
        }
        // 跳出while的处理
        //if ((lhs < nums.length) && (nums[lhs] > target)) {
        //    return lhs;
        //} else {
        //    return -1;
        //}
        return lhs;
        // 测试一下
        // nums = [], target = 0, rtn = -1
        // nums = [1,2,2], target = 1
        // lhs = 0, rhs=3; mid = 1, nums[1]=2 > target, rhs = 1; mid = 0, nums[0]=1==target, lhs=1; break, return 1
        // nums = [1,2,2], target = 2
        // lhs = 0, rhs=3; mid = 1, nums[1]=2 ==target, lhs = 2; mid = 2, nums[2]=2==target, lhs=3; break, return 3 
    }
    
    public int[] searchRange(int[] nums, int target) {
        int [] rtn = new int[2];//Array(2);
        
        // 因为是整数吗，小一位就行了
        int lpos = binarySearch(nums, target-1);
        int rpos = binarySearch(nums, target);
        // 需要处理一下rpos
        rtn[0] = lpos;
        if (lpos == -1 || lpos == nums.length) {
            rtn[0] = -1;
            rtn[1] = -1;
        } else if (nums[lpos] != target) {
            rtn[0] = -1;
            rtn[1] = -1;
        } else {
            rtn[0] = lpos;
            rtn[1] = rpos-1;
        }
        return rtn;
    }
}


public class Main {
  public static void main(String[] args) {
    Solution gua = new Solution();
    int [] rtn;
    int [] nums = {5,7,7,8,8,10};
    int target = 8;
    rtn = gua.searchRange(nums, target);
    System.out.println("expect value = [3,4], actual value = [" +rtn[0]+","+rtn[1]+ "]");
    
    target = 6;
    rtn = gua.searchRange(nums, target);
    System.out.println("expect value = [-1,-1], actual value = [" +rtn[0]+","+rtn[1]+ "]");
   
    nums = new int[]{}; 
    rtn = gua.searchRange(nums, target);
    System.out.println("expect value = [-1,-1], actual value = [" +rtn[0]+","+rtn[1]+ "]");
  }
}



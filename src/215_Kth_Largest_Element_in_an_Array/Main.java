
class Solution {
  // Runtime: 22 ms, faster than 5.65% 
  // Memory Usage: 39.3 MB, less than 65.31%
  public int findKthLargest(int[] nums, int k) {
    // 练习一下二分查找，这里左右边界都是有效的，while循环属于找不到不罢休的情况
    int lhs = 0, rhs = nums.length-1;

    // 一直找到k-1那个位置为止(按照模版写法应该是lhs <= rhs)
    // while (true) {
    while (lhs <= rhs) {
      // 这里的mid由partition函数来确定，后者将nums拆分为两部分；
      // 0~mid-1都是比nums[mid]大，mid~lenght-1都比nums[mid]小
      int mid = partition(nums, lhs, rhs);
      if (mid == k-1)
        return nums[mid];
      
      if (mid > k-1) {
        // 说明0到mid所在的位置长度超过了k，要向左压缩
        // 使用mid还是mid-1需要与partition结合考虑
        rhs = mid - 1;
      } else {
        lhs = mid + 1;
      }
    }
    return -1;// 原本采用while(true)的循环，现在采用lhs <= rhs，加一个返回值好歹让代码看起来人性一点
  }

  // 这个函数基于quick排序，让pivot左侧数据都大于pivot
  int partition(int [] nums, int left, int rhs) {
    int pivot = nums[left];
    // 下面是内部循环的左右双指针
    int l = left + 1, r = rhs;
    while (l <= r) {
      if (nums[l] < pivot && pivot < nums[r]) { //如果没有这个交换，可能会死循环
        // 让nums[l]和nums[r]交换，并且l++，r--
        // 这样的目的是让左侧都大于pivot
        int tmp = nums[l];
        nums[l] = nums[r]; nums[r] = tmp;
        // l++; r--; 这一行可以不需要
        //swap(nums[l++], nums[r--]);
      }
      // 再分别处理其他的情况，完美解决了问题
      if (nums[l] >= pivot) ++l;
      if (pivot >= nums[r]) --r;
    }
    // r那个位置是大于pivot的值，将其与pivot交换，得到pivot的正确位置
    nums[left] = nums[r]; nums[r] = pivot;
    // swap(nums[left], nums[r]);
    return r;//返回的是pivot的正确位置
  }
}

public class Main {
  public static void main(String[] args) {
    Solution gua = new Solution();
    int rtn;

    int [] nums = {3,5,1,2};
    int k;
    rtn = gua.findKthLargest(nums, k=2);
    System.out.println("expect value = 3, actual value = " +rtn);
    
    nums = new int[]{3,2,3,1,2,4,5,5,6}; 
    rtn = gua.findKthLargest(nums, k=2);
    System.out.println("expect value = 5, actual value = " +rtn);
  }
}


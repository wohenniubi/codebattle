
import java.util.*;

class Solution {
    // Runtime: 3 ms, faster than 97.15%
    // Memory Usage: 58.3 MB, less than 7.47% 
    public List<Integer> findClosestElements(int[] arr, int k, int x) {
        int lhs = 0;// k个连续元素首元素的合法最左pos
        int rhs = arr.length-k;// k个连续元素的首元素的合法最右pos
        // while (lhs <= rhs) { 大意啦大意啦
        while (lhs < rhs) {
            int mid = lhs + (rhs - lhs)/2;
            if (arr[mid] >= x) {
                // x |  arr[mid] ... arr[mid+k]
                rhs = mid;
            } else if (arr[mid+k] <= x) {
                // arr[mid] ... arr[mid+k] |  x
                lhs = mid + 1;
            } else if (x - arr[mid] > arr[mid+k] -x) {
                // arr[mid] .. | x | arr[mid+k]
                lhs = mid + 1;
            } else {
                // arr[mid] | x | .. arr[mid+k]
                rhs = mid;
            }
        }
        // 做个测试: [1,2,3,4,5] k = 4, x = 3
        // lhs = 0, rhs = 1; mid = 0, arr[mid]=1, arr[mid+4]=5, rhs = 0; mid = 0;
        Integer[] tmp = new Integer[k];// java初学者: tmp需要和List一样的类型，要不然asList时报错
        final int flhs = lhs;// local variables referenced from a lambda expression must be final or effectively final 
        Arrays.setAll(tmp, p-> arr[p+flhs]);// setAll这里的第二个参数是lambda函数哟，入参p是tmp的index哟
        List<Integer> rtn = Arrays.asList(tmp);
        // 或者for loop + add操作
        // List<Integer> rtn = new ArrayList<Integer>();
        // for (int i = lhs; i<lhs+k; ++i) rtn.add(arr[i]);
        return rtn;
    }
}

public class Main {
  public static void main(String[] args) {
    Solution gua = new Solution();
    int [] arr = {1,2,3,4,5};
    int [] nums = {5,7,7,8,8,10};
    int k = 4, x = 3;
    List<Integer> rtn = gua.findClosestElements(arr, k, x);
    System.out.println("expect value = [1,2,3,4], actual value = [");
    for (int i : rtn) System.out.println(i + ", ");
  }
}

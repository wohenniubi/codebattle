
class Solution {
    // Runtime: 2 ms, faster than 36.24%
    // Memory Usage: 38.2 MB, less than 11.80% 
    public int reverse(int x) {
        // 采用扩大处理
        long rtn = 0;
        
        while (x != 0) {
            rtn = rtn * 10 + x%10;
            // 如果超过4字节的范围，返回0
            // rtn > Integer.MAX_VALUE || rtn < Integer.MIN_VALUE
            if (rtn > 2147483647 || rtn < -2147483648) {
                return 0;
            }
            x /= 10;// 又大意了，死循环
        }
        return (int)rtn;
    }

    //Runtime: 1 ms, faster than 100.00%
    //Memory Usage: 36.1 MB, less than 66.43%
    public int reverse1(int x) {
        int rtn = 0;
        
        // 采用比较法，不使用long类型，但是该方法对于LC的C++会报错，因为C++会检查越界
        while (x != 0) {
            int tmp = rtn;
            // 每次rtn提取x的最低位进行更新
            // 初次进来时肯定不会越界，而越界处理在rtn扩大之后，所以可以认为过去的处理的都不会导致问题
            rtn = rtn * 10 + x%10; // 非常经典的操作，取模对于负数也同样试用
            if (rtn/10 != tmp) {
                return 0;
            }
            // 别大意了，这里把x更新
            x /= 10;
        }
        return rtn;
    }
}

public class Main {
  public static void main(String[] args) {
    Solution gua = new Solution();
    int x, rtn;

    rtn = gua.reverse(x = 123);
    System.out.println("expect value = 321, actual value = " + rtn);
    
    rtn = gua.reverse(x = -123);
    System.out.println("expect value = -321, actual value = " + rtn);
    
    rtn = gua.reverse(x = 1534236469);
    System.out.println("expect value = 0, actual value = " + rtn);
    
    rtn = gua.reverse(x = 0);
    System.out.println("expect value = 0, actual value = " + rtn);
    
    rtn = gua.reverse(x = 120);
    System.out.println("expect value = 21, actual value = " + rtn);
  }
}



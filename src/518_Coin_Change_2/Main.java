
class Solution {
    //Runtime: 2 ms, faster than 99.97% 
    //Memory Usage: 36.4 MB, less than 81.19% 
    public int change(int amount, int[] coins) {
        int types = coins.length;
        // LinkedList<> dp = new LinkedList(amount+1);
        int [] dp = new int[amount+1];// 不记得怎么进行2维数组的初始化，只好进行空间压缩
        
        // 无限背包问题，dp为types行，amount+1列
        // 第i行j列表示：仅包含coins[0]~coins[i]这些面额的硬币时，总价值为j时的组合个数
        // dp[i][j] = dp[i-1][j-coins[i]] + dp[i-1][j];
        // dp[0][0] = 1
        dp[0] = 1;
        
        for (int t = 0; t < types; ++t) {
            for (int v = coins[t]; v <= amount; ++v) {
                // dp[t][v] = dp[t-1][v-coins[t]] + dp[t-1][v];
                dp[v] = dp[v-coins[t]] + dp[v];
            }
        }
        return dp[amount];
        
        // 测试一下[1,2,5] target = 5
        //   1 2 3 4 5
        // 1 0 0 0 0 0 initial dp
        //  \|\|\|\|\|
        // 1 1 1 1 1 1 只使用面额coins[0]时的组合数
        //  \ \|\|\|\| 
        //    \|\|\|\|
        // 1 1 2 2 3 3 只使用面额coins[0]和coins[1]时，4 = 1,1,1,1, 4 = 2,2, 4=1,2,1
        //  \        |
        //    \      |
        //      \    |
        //        \  |
        //          \|
        //           4 使用coins[0]，coins[1] 和coins[2]时的组合数
    }
}

public class Main {
  //public static int main(String argv) { 这里输入是个[]
  public static void main(String [] args) {
    int rtn;
    Solution gua = new Solution();

    int amount;
    int [] coins = {1,2,5};
    rtn = gua.change(amount = 5, coins);
    //System.print.ln("expact value = 4, actual value = " + rtn);
    System.out.println("expact value = 4, actual value = " + rtn);
  }
}



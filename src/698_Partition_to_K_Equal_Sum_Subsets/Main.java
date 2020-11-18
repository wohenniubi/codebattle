
class Solution {
    public boolean canPartitionKSubsets(int[] nums, int k) {
        int sum = 0;
        for (int i = 0; i < nums.length; ++i) sum += nums[i];
        // if (sum % k) return false; //不能像C++一样写呢
        if ((sum % k) != 0) return false;
        sum /= k;
        
        // int[] visited = new int[](nums.length); 大意啦大意啦
        int[] visited = new int[nums.length];
        // return findValidSol(nums, sum, 0, k, visited); // 必须再加一个pos，来压缩（pruning）路径，否则会超时
        return findValidSol(nums, sum, 0, 0, k, visited);
    }
    
    // boolean findValidSol(int[] nums, int target, int sum, int k, int[] visited) {
    boolean findValidSol(int[] nums, int target, int sum, int pos, int k, int[] visited) {
        // 返回条件有点不明确，先空着
        if (sum == target) {
            k--;
            if (k==0) return true;
            sum = 0;// 使得sum清空
            pos = 0;// 使得pos清空，要不然pos到最后了，都不能被重置
        }
        
        // for (int i = 0; i < nums.length; ++i) { // 每次都从0开始的话，复杂度变成了O(n^n)，这样在n=16时就搞不定了
        for (int i = pos; i < nums.length; ++i) {
            // 对于已经大于target或者超过target的组合，就不考虑了，pruning掉
            // if (visited[i] || sum + nums[i] > target) continue; 好吧呀，java不允许从int到bool的转换，也算是保护吧
            if ((visited[i] == 1) || sum + nums[i] > target) continue;
            
            visited[i] = 1; sum += nums[i];
            // if (findValidSol(nums, target, sum, k, visited)) return true;
            // if (findValidSol(nums, target, sum, pos+1, k, visited)) return true; 别大意啊，不是从pos往后，是从当前i位置往后
            if (findValidSol(nums, target, sum, i+1, k, visited)) return true;
            
            visited[i] = 0; sum -= nums[i];
        }
        // 这里有没有必要增加memoize数组??
        return false;
    }
}

public class Main {
  public static void main(String[] args) {
    Solution gua = new Solution();
    boolean rtn;
    int [] nums;
    int k;
    nums = new int[]{4,3,2,3,5,2,1}; k=4;
    rtn = gua.canPartitionKSubsets(nums, k);
    System.out.println("expect value = true, actual value = "+ rtn);
    
    nums = new int[]{10,10,10,7,7,7,7,7,7,6,6,6}; k=3;
    rtn = gua.canPartitionKSubsets(nums, k);
    System.out.println("expect value = true, actual value = "+ rtn);
  
    nums = new int[]{2,2,2,2,3,4,5}; k=4; 
    rtn = gua.canPartitionKSubsets(nums, k);
    System.out.println("expect value = false, actual value = "+ rtn);
    
    //nums = new int[]{}; 
    //rtn = gua.canPartitionKSubsets(nums, k);
    //System.out.println("expect value = true, actual value = "+ rtn);
  }
}


#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        int lhs = 0, rhs = nums.size();

        // 如果不加shuffle函数，复杂度在最坏情况下是O(n^2)，比较慢
        //Runtime: 140 ms, faster than 8.63%
        //Memory Usage: 9.8 MB, less than 97.31%
    
        // 这里再加一个shuffle函数，可以显著改善运行时间，近似于O(n)
        //Runtime: 8 ms, faster than 83.62%
        //Memory Usage: 10 MB, less than 84.68%
        function<void(vector<int>&)> shuffle = [](vector<int> &nums) {
            int size = nums.size();
            for (int i = 0; i < size; ++i) {
                int pos = rand()%(size-i); // 0 <= pos < (size-i) 
                swap(nums[i], nums[pos+i]); // pos+i, i<= pos < size
            }
            // 这样shuffle之后的nums有n!种情况，是最均匀的
        };
        shuffle(nums);

        // 这个函数用于查找[lhs, rhs)之间的pivot
        // 本题是查找最大值，为了与k对应，应该把较大值放在pivot左边
        function<int(vector<int>&, int, int)> findPivot = [](vector<int>& nums, int lhs, int rhs)->int {
            if (lhs >= rhs) return -1;
            
            int pos = rhs-1;// 初始化pivot为最右侧的点
            for (int i = lhs; i < pos; ++i) {
                //if (nums[i] < nums[pos]) {
                if (nums[i] > nums[pos]) {
                    swap(nums[i], nums[lhs]);
                    lhs++;// 这样lhs始终保持的是大于nums[pos]的值
                }
            }
            swap(nums[lhs], nums[pos]);
            return lhs;
        };
        
        while (lhs < rhs) {
            // 返回pivot的index，注意是0-index哟
            int pos = findPivot(nums, lhs, rhs);
            if (pos == k-1) {
                return nums[pos];
            } else if (pos > k-1) {
                //说明需要查找的部分在nums的左半部分，rhs更新为pos也不会导致重复计算
                rhs = pos;
            } else {
                lhs = pos+1;// pos已经计算过了，所以要增加1
                //k -= (pos+1);// pos+1才是长度
                //由于findPivot计算的是pivot的绝对index，所以这里不需要修改k
            }
        }
        
        return -1;
    }
};

int main() {
  Solution gua;
  int rtn, k;
  vector<int> nums;

  rtn = gua.findKthLargest(nums={3,5,1,2}, k = 2);
  cout << "expect result = 3, actual result = " << rtn << endl;

  rtn = gua.findKthLargest(nums={3,2,1,5,6,4}, k = 2);
  cout << "expect result = 5, actual result = " << rtn << endl;

  rtn = gua.findKthLargest(nums={3,2,1,5,6,4}, k = 4);
  cout << "expect result = 3, actual result = " << rtn << endl;

  rtn = gua.findKthLargest(nums={6,5,4}, k = 2);
  cout << "expect result = 5, actual result = " << rtn << endl;

  return 0;
}



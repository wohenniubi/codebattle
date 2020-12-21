
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    //Runtime: 296 ms, faster than 9.09%
    //Memory Usage: 41.2 MB, less than 37.50%
    double findMaxAverag(vector<int> &nums, int k) {
        int n = nums.size();
        vector<double> sums(n+1,0);
        
        // 函数式编程真香
        double lhs = *min_element(nums.begin(), nums.end(), [](int A, int B)->bool{ return A < B;});
        double rhs = *max_element(nums.begin(), nums.end());
        
        while (lhs + 1e-6 < rhs) {
            // 这里是针对average来进行二分查找，很硬核
            double mid = lhs + (rhs-lhs)/2;
            //double minSum; 不要大意啊！！local 变量要初始化
            double minSum = 0;
            bool check = false;
            for (int i = 1; i <= n; ++i) {
                // 每个数都要减去average，然后将这个差值进行求和
                sums[i] = sums[i-1] + (nums[i-1] - mid);
                if (i >= k) {
                    // 由于sums是差值的求和数组，因此sums[i]-sums[i-k]得到的是nums[i-k]-mid, ...nums[i-1]-mid的sum
                    // 不过这里是借助差值求和数组，找到了左边界为0,右边界在[0,i-k-1]的一个最小差值sum数组；
                    // 利用这个最小差值sum数组，sums[i] - minSum就可以得到一个长度大于等于k的子数组的最大差值和
                    minSum = min(minSum, sums[i-k]);
                }// 这里借助差值sum数组和min处理，巧妙的避免了两次for loop
                
                // 这里如果最大差值和>0，设置一个tag，就可以提前跳出了
                if (i >= k && sums[i] > minSum) {
                    check = true;
                    break;
                }
            }
            if (check) {
                // 如果存在一个最大差值和>0，说明average小了——这是因为如果mid真的是最大平均数
                // 那么仅有能够凑出最大平均数的那个子数组能够得到差值和为0，其他都为负数
                lhs = mid;
            } else {
                rhs = mid;
            }
        }
        
        return lhs;// 跳出while循环时lhs+1e-5>= rhs，不过此时已经是满足条件的值了，被夹逼出来了
    }
};

int main(int argc, const char * argv[]) {
    // insert code here...
    Solution gua;
    vector<int> nums;
    int k;
    double rtn;
    rtn = gua.findMaxAverag(nums={1,2,3,4}, k=2);
    cout << "expect value = 3.5, actual value = " << rtn << endl;
    
    return 0;
}


#include <iostream>
#include <vector>
#include <functional>

using namespace std;

class Solution {
public:
    //Runtime: 40 ms, faster than 68.28%
    //Memory Usage: 15.7 MB, less than 87.63%
    vector<int> sortArray(vector<int>& nums) {
        if (nums.size() < 2) return nums;
        
        // 想直接调用sort函数，哈哈
        // sort(nums.begin(), nums.end());
        // return nums;
        // 这里findPivot是针对[bgn, end)里面的subarray进行处理
        function<int(vector<int>&, int, int)> findPivot = [&](vector<int>& nums, int bgn, int end) ->int {
            int high = end-1;
            int pivot = nums[high];
            // 然后从pivot+1到bgn-1进行划分，ascending order，双指针
            // lhs总是记录了比当前pivot小的数，另一个快指针不断扫描
            int lhs = bgn;
            for (int i = bgn; i < high; ++i) {
                if (nums[i] < pivot) {
                    swap(nums[lhs], nums[i]);
                    lhs++;
                }
            }
            // 跳出循环之后再进行最后一次swap操作，lhs始终保持的是大于pivot的值
            swap(nums[lhs], nums[high]);
            return lhs;
        };
        
        // 采用的是递归方法，试着用quick sort；注意序列sort与链表sort不同，后者过程中需要打断指针
        // 一定要写返回类型，要不然编译错误。。。
        function<void(vector<int>&, int, int)> quickSort = [&](vector<int> &nums, int bgn, int end)->void {
            // 返回条件，貌似是in place的sort，那都不需要返回vector<int>了
            if (bgn + 1 >= end) return;
            
            // 首先将[bgn,end)的子数组进行划分，找到pivot
            int pivot = findPivot(nums, bgn, end);
            
            // 对[bgn,pivot)和[pivot,end)这两部分subarray分别进行quickSort
            quickSort(nums, bgn, pivot); // 这里不用去掉pivot是因为不会再包含pivot
            //quickSort(nums, pivot, end); 切记右分支要排除pivot，要不然会导致死循环
            quickSort(nums, pivot+1, end);
        };
        
        //return quickSort(nums, 0, nums.size());
        quickSort(nums, 0, nums.size());
        return nums;
    }
};

ostream & operator<< (ostream &os, vector<int> &rtn) {
    os << "[";
    for (auto val : rtn) os << val << ", ";
    os << "]" << endl;
    return os;
}

int main(int argc, const char * argv[]) {
    Solution gua;
    
    vector<int> nums{5,3,7,2,1,6};
    cout<<"before reverse = " << nums;
    gua.sortArray(nums);
    cout<<"after reverse  = " << nums;
    return 0;
}

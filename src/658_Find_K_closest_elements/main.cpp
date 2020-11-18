
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    // Runtime: 68 ms, faster than 90.76%
    // Memory Usage: 31.5 MB, less than 80.47% 
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
      int lhs = 0, rhs = arr.size()-k;// 因为1 <= k <= arr.length， 所以不会越界
      
      // 这里还利用了这k个elements必定是连着的特性，这里直觉一下，就不证明了吧
      while (lhs < rhs) {
          int mid = lhs + (rhs - lhs)/2;
          // 这里是arr[mid],arr[mid+1]...arr[mid+k-1]这个k长度的数组
          // 与arr[mid+1],arr[mid+2]...arr[mid+k]这个k长度的数组进行比较
          // 中间的arr[mid+1]...arr[mid+k-1]都被抵消掉
          
          // abs的方法败在了arr1 = {1,1,2,2,2,2,2,3,3}, k=3, x=3
          // 这里问题出在x=3 位于[2,2,2,2]的右边，且arr的值相等，如果取绝对值，会导致左移（缩小rhs），
          // 此时相对于墨守lhs（缩小rhs），应该是右移（增大lhs）才有可能获得距离更小的起始点，因此拆除abs
          // 但是为了保证向左向右的指示不变，写为x - arr[mid]和arr[mid] -x，这样可以照顾所有段，
          // 即x<arr[mid], arr[mid] <x<arr[mid+k], x > arr[mid+k]
          //if (abs(x - arr[mid]) > abs(arr[mid+k] -x)) {
          //     lhs = mid+1;
          // } else {
          //     // 在小于的情况下，肯定是保留arr[mid]作为起点，不会以arr[mid+1]为起点
          //     // 而等于的情况下，题意要保留较小的值，而arr已经排序，较小的值也是arr[mid]，故左移
          //     rhs = mid;
          // }
          if (x > arr[mid+k]) {
              lhs = mid+1;
          } else if (x < arr[mid]) {
              rhs = mid;
          } else {
              // 而x-arr[mid] > arr[mid+k] -x的写法其实可以涵盖x > arr[mid+k]和x < arr[mid]的分支，
              // 因此可以简化为findClosestElements1的写法
              if (x-arr[mid] > arr[mid+k] -x) {
                  lhs = mid+1;//等于的时候保留小的，即保留lhs不变，即移动rhs
              } else {
                  rhs = mid;
              }
          }
      }// lhs就是起点
      
      //vector<int> rtn(k);
      //for (int i = 0; i < k; ++k) rtn[i] = arr[lhs+i];
      // vector<int> rtn(arr.begin()+lhs, arr.begin()+lhs+k-1); 大意了，这种方式也是左开右闭
      vector<int> rtn(arr.begin()+lhs, arr.begin()+lhs+k);
      return rtn;
  }

  vector<int> findClosestElements2(vector<int>& arr, int k, int x) {
      vector<int> rst = arr;
      // this method is a linear method O(n) complexity
      while (rst.size() > k) {
          // Assume x is within the range of arr,
          // this is feasible since arr is monotonic.
          // Actually, the position of x won't affect the condition, because assume
          // (1) x is smaller than rst.front(), thus we always remove the rightmost point
          // (2) x is bigger than rst.back(), thus we always remove the left most point
          // (3) x is in the middle of rst, thus we remove left and right most points in turns
          if (x - rst.front() <= rst.back() - x) {
              rst.pop_back();
          } else {
              rst.erase(rst.begin());
          }
      }
      
      return rst;
  }   
};

ostream & operator<< (ostream& os, vector<int> &rtn) {
  os << "[";
  for (int i = 0; i < rtn.size(); ++i) {
    os << rtn[i] <<(i==(rtn.size()-1)?"":",");
  }
  os << "]";
  return os;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    Solution gua;
    vector<int> rtn;
    vector<int> arr1;
    int k, x;
    rtn = gua.findClosestElements(arr1 = {1,1,2,2,2,2,2,3,3}, k=3, x=3);
    cout << "expect value = [2,3,3], actual value = " << rtn << endl;
    //for (auto i : rst) cout << i << ", "; cout << endl;
    
    rtn = gua.findClosestElements(arr1 = {1, 2, 3, 4, 5}, k=4, x=3);
    cout << "expect value = [1,2,3,4], actual value = " << rtn << endl;
    //for (auto i : rst) cout << i << ", "; cout << endl;
    
    std::cout << "Hello, World!\n";
    return 0;
}


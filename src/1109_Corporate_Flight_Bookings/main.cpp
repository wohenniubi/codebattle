#include <map>
#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    //Runtime: 248 ms, faster than 66.32%
    //Memory Usage: 77.9 MB, less than 5.53% `
    vector<int> corpFlightBookings(vector<vector<int>>& bookings, int n) {
        // 这道题属于前缀和数组的范畴
        // 第一感觉是使用一个数组来保存预定的信息，保存起点数据和终点数据，最后来一次遍历
        // 1    2    3    4    5
        // |-10-|
        //      |-20-|
        //      |------25------|
        // 然后在此基础上优化一下数组，使用ordered_map来操作，这样节省空间且能够遍历
        map<int, int> dict;
        for (auto &book : bookings) {
            int bNo = book[0], eNo = book[1], num = book[2];
            dict[bNo] += num;
            dict[eNo+1] -= num;
        }
        // 结束之后{1:10, 2:45, 3:-10, 4:-20, 6:-25}
        
        vector<int> rtn;//来一次遍历吧
        // 以下操作无法应对[2,2,10][2,2,20]返回[0,30]的情况，所以稍微修改下
        // int sum = 0, prev = -1;
        // for (auto [fNo, num] : dict) {
        //     sum += num;
        //     if (prev == -1) {
        //         prev = fNo;
        //         rtn.push_back(num);
        //     } else {
        //         // rtn.resize(rtn.size() + fNo-prev, sum);
        //         rtn.insert(rtn.end(), fNo-prev-1, rtn.back());
        //         rtn.insert(rtn.end(), sum);
        //         prev = fNo;
        //     }
        // }
        int sum = 0, prev = 0;
        for (auto [fNo, num] : dict) {
            sum += num;
            // 首先扩充前面航班的座位个数
            rtn.insert(rtn.end(), fNo-prev-1, (rtn.size()?rtn.back():0));
            // 再加入当前航班的座位数量
            rtn.insert(rtn.end(), sum);
            prev = fNo;
        }
        
        // rtn.pop_back();// 别忘了最后一个0是多余的哟 
        // 如果使用map的话，不能直接去掉最后一个数，还需要考虑n：
        // 不足n的要补上最后的0，超过n的要去掉，否则会挂在下面两个个例子上
        // [[2,3,30],[2,3,45],[2,3,15],[1,3,15]], n = 4 -> rtn = [15,105,105,0]
        // [1,1,10], n = 4 -> rtn = [10,0,0,0]
        rtn.resize(n, rtn.back());
        return rtn;
    }
};

ostream & operator<<(ostream &os, vector<int> &rtn) {
  os << "[";
  for (auto val : rtn) os << val << ",";
  os << "]";
  return os;
}

int main() {
  Solution gua;
  int n;
  vector<int> rtn;
  vector<vector<int>> books;
  
  rtn = gua.corpFlightBookings(books={{2,2,10}}, n = 3);
  cout << rtn << endl;
  
  rtn = gua.corpFlightBookings(books={{1,2,10},{2,3,20},{2,5,25}}, n = 5);
  cout << rtn << endl;
  
  rtn = gua.corpFlightBookings(books={{1,1,40}}, n = 4);
  cout << rtn << endl;
  return 0;
}



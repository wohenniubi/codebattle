
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    //Runtime: 68 ms, faster than 13.91%
    //Memory Usage: 13.3 MB, less than 49.01%
    // 以后一看到这样的题，就想到用二分查找，用distance来查找
    double minmaxGasDist(vector<int>& stations, int k) {
        double lhs = 0, rhs = stations.back() - stations.front();// 用最远的距离作为rhs
        
        // while (lhs + 1e-6 > rhs) { 大意了啊大意了啊
        while (rhs - lhs > 1e-6) {
            double dist = (rhs-lhs)/2 + lhs;
            
            // 以这个值dist作为penalty(最大distance），看看有多少相邻的stations超过这个距离
            if (helper(stations, k, dist)) {
                lhs = dist;
            } else {
                rhs = dist;
            }
            // 对于浮点数，lhs和rhs的更新不需要加减1
        }
        
        return lhs;
    }
    
    bool helper(vector<int>& adjs, int k, double dist) {
        int cnt = 0;
        for (int i = 1; i < adjs.size(); ++i) {
            // 两个加油站距离大于超过dist，为了保证最终的penalty(最大距离)不超过dist，两者之间需要新增一个点
            // if (adjs[i] - adjs[i-1] > dist) 没理解题意，这里应该用除法，超过多少倍，新增多少个节点
            //    ++cnt;
            cnt += (adjs[i] - adjs[i-1])/dist;
        }
        return (cnt > k);// 大于k表明，为了保证dist这个最大距离，实际要增加的站点超过了k，那么说明目标dist取小了，要提升下限
    }
};

int main(int argc, const char * argv[]) {
    Solution gua;
    vector<int> stations;
    int k;
    double rtn;
    
    rtn = gua.minmaxGasDist(stations = {1,2,3,4,5,6,7,8,9,10}, k = 9);
    cout << "expect value = 0.5, actual value = " << rtn << endl;
    
    rtn = gua.minmaxGasDist(stations = {10, 19, 25, 27, 56, 63, 70, 87, 96, 97}, k = 3);
    cout << "expect value = 9.67, actual value = " << rtn << endl;

    rtn = gua.minmaxGasDist(stations = {23,24,36,39,46,56,57,65,84,98}, k = 1);
    cout << "expect value = 14, actual value = " << rtn << endl;

    return 0;
}

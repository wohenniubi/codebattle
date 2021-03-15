
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int getSteps(string &ring, int prev, char T, bool isClockWise) {
        int lenR = ring.size();
        
        int cnt = 0;
        for (int pos = prev; cnt < lenR; ++cnt) {
            // 避免index越界，且加入了顺时针和逆时针
            //int pos = (cnt+prev)%lenR;
            //int pos = ((cnt+prev+(isClockWise?1:-1))%lenR + lenR) %lenR;
            if (ring[pos] == T)
                break;
            pos = (pos + (isClockWise?1:-1) + lenR)%lenR;
        }
        //return min(cnt, abs(cnt-lenR));
        return cnt;
    }
    
    // 从当前ring的位置，完成key.substr(posK)的转动的最小值
    // 首先想想API的入参数有哪些，我原本觉得只需要一个状态就够了，例如：key的pos
    // 不过发现如果key有两个char，例如：AB，而假如ring是八卦图，A位于巽挂和离挂，B位于震挂，
    // 那么从乾挂开始，第一次greedy选择巽位的A，那么完成AB需要7步；而第一次选择离挂的A，
    // 完成AB只需要5步，可见与ring的state有关
    int backTrackMemo(string &ring, string &key, int posR, int posK) {
        if (posK == key.size())
            return 0;
        
        // 然后查询是否存在这个结果，如果存在则直接返回,TODO
        string tmp = to_string(posR)+","+to_string(posK);
        if (dict.count(tmp))
            return dict[tmp];
        
        int size = ring.size();
        // 不存在的话就进行选择，两种选择，从ring[posR]的顺时针或者逆时针找key[posK]
        int lhs = getSteps(ring, posR, key[posK], true);
        int rhs = getSteps(ring, posR, key[posK], false);
        
        int rtn = 0;
        if (0 == lhs && 0 == rhs) {
            // 这种情况只需要执行一种选择
            rtn = backTrackMemo(ring, key, posR, posK+1)+1;// 按一下spell
        } else {
//            rtn = 1 + min(backTrackMemo(ring, key, (posR+lhs)%size, posK+1),
//                          backTrackMemo(ring, key, (posR-rhs+size)%size, posK+1)); 大意了，忘记决策的次数了
            rtn = 1 + min(lhs + backTrackMemo(ring, key, (posR+lhs)%size, posK+1),
                          rhs + backTrackMemo(ring, key, (posR-rhs+size)%size, posK+1));
        }
        
        return dict[tmp] = rtn; // 注意要保存到memo TODO
    }
    
    //Runtime: 72 ms, faster than 30.04%
    //Memory Usage: 26.4 MB, less than 14.80%
    unordered_map<string, int> dict;
    int findRotateSteps(string ring, string key) {
        dict.clear();
        return backTrackMemo(ring, key, 0, 0);
    }
//    int findRotateSteps(string ring, string key) {
//        // 我感觉这道题有点像Edit distance，也是用dp模版，试试吧
//
//        // return dpMinRotateSteps(ring, key, 0, 0);
//        int lenR = ring.size(), lenK = key.size();
//
//        vector<vector<int>> dp = vector<vector<int>>(lenR+1, vector<int>(lenK+1));
//        // 是否需要初始化TODO
//
//        // 从左到右，从上到下更新取值，因为ring上面一定可以找到对应的char
//        for (int j = 1; j <= lenK; ++j) {
//            for (int i = 1; i <= lenR; ++i) {
//                if (dp[i][j-1]) {
//                    // 上一个key连贯才OK，因此可以确定初始化的值
//                    int steps = getSteps(ring, i-1, key[j-1], true);
//                    dp[i][j] = steps + 1;// spell会占用一次
//                }
//                // 此时dp[][0]刚好是0，对应12点钟的乾挂，所以初始化为0没毛病
//
//                int steps = getSteps(ring, i-1, key[j-1], true);
//                // 两种选择，clockwise和anticlockwise
//                if (ring[i-1])
//            }
//        }
//        return 0;//返回哪个值：TODO
//    }
};

int main(int argc, const char * argv[]) {
    Solution gua;
    int rtn;
    string ring, key;
    
    rtn = gua.findRotateSteps(ring = "godding", key="gd");
    cout << "expect value = 4, actual value = " << rtn << endl;
    return 0;
}

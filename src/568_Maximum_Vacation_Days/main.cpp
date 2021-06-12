
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    //Runtime: 216 ms, faster than 58.27%
    //Memory Usage: 23.5 MB, less than 79.86%
    int maxVacationDays(vector<vector<int>>& flights, vector<vector<int>>& days) {
        int citys = days.size(), weeks = days[0].size();
        vector<int> dp(citys, INT_MIN);// 初始化为INT_MIN很机智啊，
        dp[0] = 0;// 将城市0初始化为0更巧妙，让代码非常简洁
        
        for (int i = 0; i < weeks; ++i) {
            vector<int> tmp(citys, INT_MIN);// 使用一个tmp，因为dp会被覆盖
            
            // 目的城市
            for (int j = 0; j < citys; ++j) {
                // 源城市
                for (int k = 0; k < citys; ++k) {
                    
                    // 如果待在源城市，或者k到j之间存在航班
                    if (k == j || flights[k][j]) {
                        tmp[j] = max(tmp[j], days[j][i] + dp[k]);
                    }
                }
            }
            dp = tmp;
        }
        return *max_element(begin(dp), end(dp));// 这样做省去了一个rtn变量，让代码非常简洁
    }

    // 下面的方法不work
    int maxVacationDays_error(vector<vector<int>>& flights, vector<vector<int>>& days) {
        // 感觉像是dp，因为很可能greedy做法会被trap到某个local minimal里面
        // 需要的状态，当前的week，当前的city A，选择包括是否有到达city B的flight
        int citys = days.size(), weeks = days[0].size();
        
        //for (int i = 0; i < citys; ++i) flights[i][i] = 1;// 认为A城市到A城市有航班
        vector<int> dp(citys);
        dp[0] = days[0][0];
        int rtn = dp[0];
        for (int j = 1; j < citys; ++j) {
            dp[j] = flights[0][j] * days[j][0];// 初始化，第一周的值等于flights与days的点乘
            rtn = max(rtn, dp[j]);
        }
        
        for (int i = 1; i < weeks; ++i) {
            vector<int> tmp = dp;
            
            // 里面两个loop循环(恼火啊)，外层循环是目的城市，内层循环是开始城市
            for (int j = 0; j < citys; ++j) {
                //int num = tmp[j] + days[j][i];//待在j城市不动
                int num = 0;
                
                // 从k城市到j城市，k是源城市
                for (int k = 0; k < citys; ++k) {
                    //num = max(num, flights[k][j]* days[j][i]); // 大意了啊！！
                    //num = max(num, flights[k][j]* days[j][i] + dp[j]); 又大意了
                    //num = max(num, flights[k][j]* days[j][i] + dp[k]); 大意3次，dp已经被更新
                    num = max(num, flights[k][j]* days[j][i] + tmp[k]);
                }
                dp[j] = num;// 更新最后一天是城市j的总休假数
                rtn = max(rtn, num);
            }
        }
        return rtn;
    }
};

int main(int argc, const char * argv[]) {
    Solution gua;
    
    int rtn;
    vector<vector<int>> flights, days;
    rtn = gua.maxVacationDays(flights={{0,0,0},{0,0,0},{0,0,0}}, days={{1,1,1}, {7,7,7}, {7,7,7}});
    cout << "expect value = 3, actual value = " << rtn << endl;

    rtn = gua.maxVacationDays(flights={{0,1,1},{1,0,1},{1,1,0}}, days={{1,3,1}, {6,0,3}, {3,3,3}});
    cout << "expect value = 12, actual value = " << rtn << endl;

    return 0;
}

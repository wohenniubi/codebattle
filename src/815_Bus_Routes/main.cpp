
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

class Solution {
public:
    //Runtime: 152 ms, faster than 92.01% 
    //Memory Usage: 51.6 MB, less than 81.54%
    // 本题思路是BFS，在原本的框架上增加一些循环，要理解为什么可以这么做
    // 因为要考虑最小值，所以常常选用BFS，需要借助一个STL容器，如果容器为空，则不可达性
    int numBusesToDestination(vector<vector<int>>& routes, int source, int target) {
        int rtn = 0;
        if (source == target)
            return rtn;// 这个是默认情况，认为不需要坐bus
        
        unordered_map<int, vector<int>> memo;// 站点值是离散的且很大，这里用哈希表好一些
        vector<int> visited(routes.size());// 由于routes长度不超过500，所以用vector会优于哈希表

        // 首先对routes进行统计，让每个stop知道有哪些route
        for (int i = 0; i < routes.size(); ++i) {
            for (auto stop: routes[i]) {
                memo[stop].push_back(i);
            }
        }
        
        queue<int> st{{source}};// 用栈作为容器，首先放入source
        while (st.size()) {
            int size = st.size();
            
            ++rtn; // 难点在哪一行代码rtn+1，因为这些站点，是要多坐1路车才可以到达的
            
            for (int i = 0; i < size; ++i) {
                // 注意提出每个站，然后找到这个站可以到其他哪些路
                //int stop = st.back(); // 怎么这么大意，要从头取呀
                int stop = st.front();
                //st.pop_back();
                st.pop();
                
                // 找到这一站所属的routes
                for (auto rID : memo[stop]) {
                    if (visited[rID]) continue;// 如果这一路已经处理结束，跳过防止重复处理
                    visited[rID] = 1;// 别大意忘了设置为1.要不然死循环
                    
                    // 从这一路里面提取所有的站点，放入st中，作为下一次while循环，也即是多一次bus
                    for (auto adj : routes[rID]) {
                        if (stop == adj) continue;
                        if (target == adj) return rtn;
                        
                        //st.push_back(adj);
                        st.push(adj);
                    }
                }
                
            }
        }
        return -1;
    }
};

int main(int argc, const char * argv[]) {
    Solution gua;
    vector<vector<int>> routes;
    int rtn, s, t;

    rtn = gua.numBusesToDestination(routes = {{0,1,6,16,22,23},{14,15,24,32},{4,10,12,20,24,28,33},{1,10,11,19,27,33},{11,23,25,28},{15,20,21,23,29},{29}}, s = 4, t = 21);
    cout << "expect value = 2, actual value = " << rtn << endl;

    rtn = gua.numBusesToDestination(routes = {{7,12},{4,5,15},{6},{15,19},{9,12,13}}, s = 15, t = 12);
    cout << "expect value = -1, actual value = " << rtn << endl;

    rtn = gua.numBusesToDestination(routes = {{1,2,7}, {3,6,7}}, s = 1, t = 6);
    cout << "expect value = 2, actual value = " << rtn << endl;
    return 0;
}

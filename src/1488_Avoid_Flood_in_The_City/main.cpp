
#include <iostream>
#include <list>
#include <vector>
#include <set>
#include <unordered_map>

using namespace std;

// 由于rains.length是10^5，所以只能是O(n)或者O(nlog)
// 基本思路是出太阳时暂时不要dry，等到下雨时再dry某一天，不过要想好用什么数据结构
//Runtime: 904 ms, faster than 30.11% 
//Memory Usage: 109.7 MB, less than 57.22%
class Solution {
    // 如果把这两个辅助STL放在函数avoidFlood外面的话，建议允许avoidFlood时先清空一下，否则Solution有了状态
    // unordered_map<int, int> helper;// 这里的[key, cnt]分别存储的是湖的id，以及这个湖最后一天下雨的日子
    // set<int> drys;// 这个set存储的是不下雨的日子
    
public:
    vector<int> avoidFlood(vector<int>& rains) {
        int size = rains.size();
        vector<int> rtn = vector<int>(size, 1);// 如果初始化为-1，貌似也可以
        unordered_map<int, int> helper;// 这里的[key, cnt]分别存储的是湖的id，以及这个湖最后一天下雨的日子
        set<int> drys;// 这个set存储的是不下雨的日子

        //for (auto rain : rains) { // 因为要记录下雨和不下雨的日子，所以得知道i
        for (int i = 0; i < size; ++i) {
            if (rains[i]) {
                int id = rains[i];// 当rain不为0时，表示的是湖的id
                if (helper.count(id)) {
                    // 如果发现这个湖被下过雨; 那么去寻找一下下过雨之后的最近的一个不下雨的日子，在那一天清空这个湖；
                    // 说明1：之所以用掉下过雨之后的晴天，因为如果晴天在下雨天之前，那么这个晴天将会没有意义；
                    // 说明2：之所以用掉雨后最早的晴天，因为如果用掉了越靠后的晴天，那么会错失原本可以清空的湖，很greedy的想法
                    auto iter = drys.upper_bound(helper[id]);
                    if (iter == drys.end())
                        return {};// 没有可用的晴天，那么就flood了
                    
                    rtn[*iter] = id;// 将晴天那一天的返回值修改为湖的id
                    drys.erase(iter);// 去掉那个晴天, erase(helper[id])的话复杂度是O(logn), erase(iter)是O(1)
                    helper[id] = i;// 大意了大意了！！！别忘了更新iter里面的最后一个下雨的日子
                    rtn[i] = -1;// 大意了大意了！！！下过去的那一天总是要让输出为-1的。。。所以初始化为-1可能会更好一些
                } else {
                    rtn[i] = -1;// 今天下雨，但是不flood，修改rtn为-1
                    helper[id] = i;// 大意了大意了，今天也要在helper里面注册这个湖的信息
                }
            } else {
                // 赶快把晴天保存起来；同时由于这一天初始化为1，所以不用做什么操作
                drys.insert(i);
            }
        }
        
        return rtn;
    }
};

// 下面的greedy方法搞不定1,0,2,0,2,1
class Solution1 {
public:
    // 花了点时间才搞清楚题目意思，明白之后感觉是策略问题
    vector<int> avoidFlood(vector<int>& rains) {
        // 首先统计所有的降雨情况？
        // [key, cnt] 分别代表湖的id，id>0，cnt表示在这个湖降水的次数
        unordered_map<int, int> stats;// [key, cnt] 分别代表湖的id，id>0, cnt貌似没啥用
        //priority_queue<pair<int, int>> helper;// 最大堆，pair<int,int>分别代表cnt次数和湖的id
        list<int> helper;// 记录的是没下雨的天所在rtn的pos，本质是个queue
        
        vector<int> rtn;// = vector<int>(rains.size(), -1);
        for (auto rain : rains) {
            if (rain) {
                // rain不为0时，表明是湖的id
                if (stats.count(rain)) {
                    // 说明这个湖曾经被下过雨，已经满了; 此时尝试找一个可用的dry去掉这个湖
                    if (helper.empty()) {
                        // 没有可选的dry日子，flood了
                        return {};// return ""; 大意了大意了
                    } else {
                        rtn[helper.back()] = rain; // 修改曾经那一天的dry为这个湖的id
                        rtn.push_back(-1);// 不要大意啊！！！这里别忘了把当天的值加进去
                        helper.pop_back();// 每次从尾部移除
                        stats.erase(rain);// 同时去掉这个湖的记录
                    }
                } else {
                    stats[rain] = rtn.size();// 存的是在rtn里的位置
                    rtn.push_back(-1);
                }
            } else {
                if (stats.size()) {
                    // 如果存在某个湖被下过雨，先把这个dry的机会留着，等待再给这个湖下雨时用
                    helper.push_front(rtn.size());// 每次加在头，
                    rtn.push_back(1);// 大意了，为保证返回值与题目要求一直，不能push_back(-1)
                } else {
                    // 如果没有哪个湖被下过雨；那么此时的dry是不需要存下来的，任意卸掉一个湖就行了
                    rtn.push_back(1);
                }
            }
        }
        
        return rtn;
    }
};

ostream & operator<< (ostream & os, vector<int> &rtn) {
    os << "[";
    for (auto pos : rtn) {
        os << pos << ", ";
    }
    
    os << "]";
    return os;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    Solution gua;
    vector<int> rtn, rains;
    
    rtn = gua.avoidFlood(rains={1,2,0,0,2,1});
    cout << "expect value = [-1,-1,2,1,-1,-1], actual value = " << rtn << endl;

    rtn = gua.avoidFlood(rains={1,0,2,0,2,1});
    cout << "expect value = [-1,1,-1,2,-1,-1], actual value = " << rtn << endl;

    rtn = gua.avoidFlood(rains={69,0,0,0,69});
    cout << "expect value = [-1,69,1,1,-1], actual value = " << rtn << endl;

    rtn = gua.avoidFlood(rains={1,2,0,2,1});
    cout << "expect value = [], actual value = " << rtn << endl;

    rtn = gua.avoidFlood(rains={1,2,3,4});
    cout << "expect value = [-1,-1,-1,-1], actual value = " << rtn << endl;

    rtn = gua.avoidFlood(rains={1,2,2});
    cout << "expect value = [], actual value = " << rtn << endl;

    return 0;
}

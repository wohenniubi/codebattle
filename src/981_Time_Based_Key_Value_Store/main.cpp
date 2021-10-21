
#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>

using namespace std;

class TimeMap1 {
public:
    // 第一眼想到的是bucket sort, 不过由于要找到不大于给定timestamp
    // 的最大timestamp, 觉得红黑树要更好一点, 所以是二分upperbound
    // Runtime: 368 ms, faster than 46.58
    // Memory Usage: 130.8 MB, less than 17.23%    

    /** Initialize your data structure here. */
    map<int,unordered_map<string, string>> dict;
    TimeMap1() {
        dict.clear();
    }
    
    void set(string key, string value, int timestamp) {
        int token = -timestamp;
        dict[token][key] = value;
    }
    
    string get(string key, int timestamp) {
        int token = -timestamp;
        // 由于想要使用map自带的lower_bound, 所以将timestamp取负数
        auto iter = dict.lower_bound(token);
        if (iter == dict.end()) {
            return "";
        } else {
            // return iter->second()[key];
            return (iter->second)[key];
        }
    }
};

class TimeMap {
public:
    /** Initialize your data structure here. */
    unordered_map<string, map<int, string>> dict;
    TimeMap() {
        dict.clear();
    }
    
    void set(string key, string value, int timestamp) {
        int token = -timestamp;
        dict[key][token] = value;
    }
    
    string get(string key, int timestamp) {
        int token = -timestamp;
        if (dict.count(key)) {
            auto iter = dict[key].lower_bound(token);
            // 不要大意啊, 要检查iter是否有效啊
            // return iter->second;
            return (iter == dict[key].end())?"":iter->second;
        } else {
            return "";
        }
    }
};

void initGua(vector<pair<string, pair<vector<string>, int>>>& list,
    vector<string> &rtn, TimeMap& gua) {
    rtn.clear();
    for (auto item: list) {
        const string & option = item.first;
        const string & key = item.second.first.front();
        const string & value = item.second.first.back();
        int timestamp = item.second.second;
        if ("set" == option) {
            gua.set(key, value, timestamp);
            rtn.push_back("");
        } else {
            rtn.push_back(gua.get(key, timestamp));
        }
    }
}

int main(int argc, const char * argv[]) {
    vector<string> rtn;
    TimeMap gua2;
    // 这些测试用例都是需要与面试官讨论的,
    vector<pair<string, pair<vector<string>, int>>> list2{{"set",{{"love","high"},10}},{"set",{{"love","low"},20}},{"get", {{"love"},5}},{"get",{{"love"},10}},{"get", {{"love"},15}},{"get", {{"love"},20}},{"get",{{"love"},25}}};
    initGua(list2, rtn, gua2);
    for (auto item : rtn)
        cout << item << ", ";
    cout << endl;

    TimeMap gua1;
    vector<pair<string, pair<vector<string>, int>>> list1{{"set",{{"ctondw","ztpearaw"},1}},{"set",{{"vrobykydll","hwliiq"},2}},{"set",{{"gszaw","ztpearaw"},3}}, {"set",{{"ctondw","gszaw"},4}}, {"get",{{"gszaw"},5}} };
    initGua(list1, rtn, gua1);
    for (auto item : rtn)
        cout << item << ", ";
    cout << endl;

    return 0;
}

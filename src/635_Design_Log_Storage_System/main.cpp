
#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>

using namespace std;

// 感觉这道题的granularity有点像掩码的效果, 然后数据的范围采用有序结构进行整理，
// 没有想到的是如何有效的进行字符串转化
//Runtime: 36 ms, faster than 79.56%
//Memory Usage: 14.7 MB, less than 40.15%
class LogSystem {
    // map<string, int> helper; 大意了，由于会出现重复的string，所以map不行
    //unordered_map<string, int> posDict = {{"Year",5}, {"Month",8}, {"Day",11}, {"Hour",14}, {"Minute",17}};
    multimap<string, int> helper;
    // 存的是(总长度 - granularity掩码部分的长度)，例如：
    // 精度为“Month”时，是把Day到最后的所有部分都掩掉，因此只保留year到Month的部分；别大意啊！！Year写成了Yesr
    unordered_map<string, int> dict = {{"Year",4}, {"Month",7}, {"Day",10}, {"Hour",13}, {"Minute",16}, {"Second",19}};
    
    // Year ranges from [2000,2017]. Hour ranges from [00,23].
    string low = "2000:00:00:00:00:00";
    string high = "2017:12:31:23:59:59";
    
//  这种修改部分string的方法搞不太定
//    string maskString(string &s, string &gra) {
//        int pos = posDict.count(gra)? posDict[gra]: s.size();
//        string tmp = s;
//
//        // 从pos开始设置两个‘0’之后设置':'
//        // "2017:01:01:23:59:59"
//        for (int i = pos; i < s.size(); i+=3) {
//            tmp[i] = '0';
//            tmp[i+1] = '0';
//        }
//        return tmp;
//    }
    string makeString(string &s, string &mask, int pos) {
        return s.substr(0, pos) + mask.substr(pos);
    }
    
public:
    LogSystem() {
        
    }
    
    void put(int id, string timestamp) {
        // helper[timestamp] = id;
        helper.insert({timestamp, id});
    }
    
    vector<int> retrieve(string s, string e, string gra) {
        // 首先获得掩码之后的string
        // string sm = maskString(s, gra);
        // string em = maskString(e, gra);
        int pos = dict[gra];
        string sm = makeString(s, low, pos);// s.substr(0, pos) + low.substr(pos);
        // 对于s.substr()这里的pos就是len，对于low.substr()这里的pos就是starting pos
        string em = makeString(e, high, pos);// e.substr(0, pos)

        auto lb = helper.lower_bound(sm);
        auto ub = helper.upper_bound(em);
        
        vector<int> rtn;
        for (; lb != ub; ++lb) {
            rtn.push_back(lb->second);
        }
        return rtn;
    }
};

ostream & operator<< (ostream &os, vector<int> & rtn) {
    os << "[";
    for (auto & i : rtn) {
        os << i << ", ";
    }
    os << "]";
    
    return os;
}

// 另一种解法，基本思路一样：把granularity当作是掩码，然后将每个记录与s和e进行比较，满足条件则存入rtn，
// 复杂度是O(n*m), m+n <= 300，对于题目要求的300数量级还是可以接受的
//Runtime: 48 ms, faster than 51.09%
//Memory Usage: 16.4 MB, less than 30.66%
class LogSystem2 {
    vector<pair<int, string>> timestamps;
    vector<string> units;
    vector<int> indices;
    
public:
    LogSystem2 () {
        // put(1, "2017:01:01:23:59:59"); 这里indices记录的是每个精度结束的pos，用哈希表貌似也行
        units = {"Year", "Month", "Day", "Hour", "Minute", "Second"};
        indices = {4, 7, 10, 13, 16, 19};// 这里很巧妙，存的是每个granularity(掩码)之后的有效长度
    }
    
    void put(int id, string timestamp) {
        timestamps.push_back({id, timestamp});
    }
    
    vector<int> retrieve(string s, string e, string gra) {
        vector<int> rtn;
        
        int idx = indices[find(units.begin(),units.end(), gra) - units.begin()];
        for (auto p : timestamps) {
            string t = p.second;
            
            // 直接使用字符串进行比较， 对精度范围内的部分进行比较 —— 真NM巧妙
            if (t.substr(0, idx).compare(s.substr(0, idx)) >= 0
                && t.substr(0, idx).compare(e.substr(0, idx)) <= 0) {
                rtn.push_back(p.first);
            }
        }
        return rtn;
    }
};

int main(int argc, const char * argv[]) {
    LogSystem gua;
    gua.put(1, "2017:01:01:23:59:59");
    gua.put(2, "2017:01:01:22:59:59");
    gua.put(3, "2016:01:01:00:00:00");
    
    vector<int> rtn;
    rtn = gua.retrieve("2016:01:01:01:01:01","2017:01:01:23:00:00","Year");
    cout << "expect value = [1,2,3], actual value = " << rtn << endl;
    
    rtn = gua.retrieve("2016:01:01:01:01:01","2017:01:01:23:00:00","Hour");
    cout << "expect value = [1,2], actual value = " << rtn << endl;
    std::cout << "Hello, World!\n";

    LogSystem gua2;
    gua2.put(1,"2005:01:05:22:16:15");
    gua2.put(2,"2003:12:12:20:30:51");
    rtn = gua2.retrieve("2005:07:10:17:43:43","2007:02:18:10:22:52","Month");
    cout << "expect value = [], actual value = " << rtn << endl;
    
    gua2.put(3,"2001:06:25:23:51:23");
    gua2.put(4,"2004:10:25:13:49:48");
    gua2.put(5,"2002:05:03:14:21:45");
    gua2.put(6,"2004:10:04:21:49:49");
    rtn = gua2.retrieve("2003:05:18:16:45:48","2007:12:05:10:36:51","Hour");
    cout << "expect value = [2,6,4,1], actual value = " << rtn << endl;
    
    gua2.put(7,"2006:05:14:18:30:30");
    gua2.put(8,"2003:04:02:22:12:41");
    gua2.put(9,"2002:02:25:13:12:24");
    gua2.put(10,"2005:01:17:23:36:39");
    gua2.put(11,"2000:07:25:12:45:16");
    gua2.put(12,"2001:08:12:16:35:55");
    gua2.put(13,"2000:10:18:18:46:38");
    rtn = gua2.retrieve("2004:09:23:19:31:46","2005:10:27:16:51:21","Year");
    cout << "expect value = [6,4,1,10], actual value = " << rtn << endl;
    
    return 0;
}


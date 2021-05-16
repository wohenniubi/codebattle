#include <iostream>
#include <unordered_map>

using namespace std;

class UndergroundSystem {
public:
    // Runtime: 160 ms, faster than 29.05%
    // Memory Usage: 57.6 MB, less than 82.72%
    unordered_map<int, pair<string, int>> caches;
    // 还有种做法是将startStation名字和endStation名字连起来，这样就不需要嵌套的unordered_map了
    unordered_map<string, unordered_map<string, pair<int,int>>> history;

    UndergroundSystem() {
        // 我能想到的办法是使用两级结构，“缓存”和“服务器”：当checkin时，数据存放于缓存里面，
        // 当checkout时，从缓存里面配对先前的checkin信息，然后从缓存移除存放到服务器中
        // 每次getAverageTime时从服务器里面获得信息，那里都是配对的历史信息
        caches.clear();
        // 这里的历史信息是以站名字作为key，pair<int,int>包含了路径sum of time，还有路径的条数
        history.clear();
    }
    
    void checkIn(int id, string stationName, int t) {
        if (caches.count(id)) {
            ; // TODO：异常处理
        }
        caches[id] = {stationName, t};
    }
    
    void checkOut(int id, string stationName, int t) {
        if (caches.count(id) == 0) {
            return;// TODO: 异常处理
        }
        
        auto &[startStation, bgnTime] = caches[id];
        int period = t - bgnTime;
        auto [sumTime, num] = history[startStation][stationName];
        history[startStation][stationName] = {sumTime + period, num+1};
        caches.erase(id);// 从cache里面移除
    }
    
    double getAverageTime(string startStation, string endStation) {
        auto [sumTime, num] = history[startStation][endStation];
        return (num)?(sumTime*1.0)/num: 0.0;
    }
};

/**
 * Your UndergroundSystem object will be instantiated and called as such:
 * UndergroundSystem* obj = new UndergroundSystem();
 * obj->checkIn(id,stationName,t);
 * obj->checkOut(id,stationName,t);
 * double param_3 = obj->getAverageTime(startStation,endStation);
 */

int main(int argc, const char * argv[]) {
    cout << "Example 1:" << endl;
    UndergroundSystem gua1;
    gua1.checkIn(45,"Leyton",3);
    gua1.checkIn(32,"Paradise",8);
    gua1.checkIn(27,"Leyton",10);
    gua1.checkOut(45,"Waterloo",15);
    gua1.checkOut(27,"Waterloo",20);
    gua1.checkOut(32,"Cambridge",22);
    cout << "expect value = 14, actual value = " << gua1.getAverageTime("Paradise","Cambridge") << endl;
    cout << "expect value = 11, actual value = " << gua1.getAverageTime("Leyton","Waterloo") << endl;
    gua1.checkIn(10,"Leyton",24);
    cout << "expect value = 11, actual value = " << gua1.getAverageTime("Leyton","Waterloo") << endl;
    gua1.checkOut(10,"Waterloo",38);
    cout << "expect value = 12, actual value = " << gua1.getAverageTime("Leyton","Waterloo") << endl;

    cout << "Example 2:" << endl;
    UndergroundSystem gua2;
    gua2.checkIn(10, "Leyton", 3);
    gua2.checkOut(10, "Paradise", 8);
    cout << "expect value = 5, actual value = " << gua2.getAverageTime("Leyton", "Paradise") << endl;
    gua2.checkIn(5, "Leyton", 10);
    gua2.checkOut(5, "Paradise", 16);
    cout << "expect value = 5.5, actual value = " << gua2.getAverageTime("Leyton", "Paradise") << endl;
    gua2.checkIn(2, "Leyton", 21);
    gua2.checkOut(2, "Paradise", 30);
    cout << "expect value = 6.6667, actual value = " << gua2.getAverageTime("Leyton", "Paradise") << endl;

    return 0;
}


#include <iostream>
#include <vector>
#include <bitset>

using namespace std;

class Solution {
public:
    vector<int> hLEDs{1,2,4,8};
    vector<int> mLEDs{1,2,4,8,16,32};

    // 记住这种取N个数中P个数的操作方法，有点像回溯的框架
    void generate(vector<int> &LEDs, int pos, int num, int bits, vector<int> &rtn) {
        if (bits < 0) return;
        // 返回条件; 必须恰好bits分配完到时候才能加入到rtn
        if (bits == 0) { //pos == LEDs.size() &&
            rtn.push_back(num);//to_string(num)
            return;
        }
        
        // 下面是选择阶段：pos到某个区间的遍历 + pos位置处的选择; 因为pos不断在压缩，所以2^h还可以接受
        for (int i = pos; i < LEDs.size(); ++i) {
            // 选还是不选，是个问题
            generate(LEDs, i+1, num + LEDs[i], bits-1, rtn);
            // 由于外部循环会执行到i+1，num，因此在同一个循环中考虑跳过LEDs[i]的情况会导致重复，得去掉
            //generate(LEDs, i+1, num, bits, rtn);
        }
        return;
    }
    
    // 方法2:采用循环试一试
    //Runtime: 0 ms, faster than 100.00%
    //Memory Usage: 6.5 MB, less than 39.33%
    vector<string> readBinaryWatch(int turnedOn) {
        vector<string> rtn;
        
        // 外部循环是分给hour的LED个数
        for (int h = 0; h <= 4 && h <= turnedOn; ++h) {
            // 那么剩下turnedOn - h个LED给minute
            int m = turnedOn - h;
            if (m > 6)
                continue;// minute的LED最多只有6个，说明分配给h的方法不合适
            
            // 好啦，开始分别构造hour和minute部分
            vector<int> hours;//vector<string> &rtn 实际编程时证明用vector<int>要好
            vector<int> minis;
            
            generate(hLEDs, 0, 0, h, hours);
            generate(mLEDs, 0, 0, m, minis);
            
            // 开始两两组合放入rtn
            for (auto & hour : hours) {
                // 这就是使用int的好处，可以直接比较数字的合法性
                if (hour > 11) continue;
            
                for (auto & mini : minis) {
                    if (mini > 59) continue;
            
                    // 这里要方便点话，必须把mini该添加的0补上
                    rtn.push_back(to_string(hour) + (mini<10?":0":":") + to_string(mini));
                }
            }
        }
        return rtn;
    }

    //Runtime: 0 ms, faster than 100.00%
    //Memory Usage: 6.2 MB, less than 95.85%
    vector<string> readBinaryWatch1(int turnedOn) {
        vector<string> rtn;
        
        for (int h = 0; h < 12; ++h) {
            for (int m = 0; m < 60; ++m) {
                // 现在判断这个h:m是具有turnon个LED灯;
                int tmp = (h<<6) + m; // 因为分钟会占用6个bit，为了防止重叠
                bitset<10> time(tmp);
                // 当比特个数等于turnon时，符合条件，转换为string
                if (time.count() == turnedOn) {
                    string hour = to_string(h);
                    //if (h<10) hour.insert(begin(hour),'0');
                    
                    string mini = to_string(m);
                    //if (m<10) mini.insert(begin(mini),'0');
                    rtn.push_back(hour+":"+((m<10)?"0":"") + mini);
                }
            }
        }
        return rtn;
    }
};

ostream &operator<<(ostream &os, vector<string> &rtn) {
    os << "[";
    for (auto & time : rtn)
        os << time << ", ";
    os << "]";
    return os;
}

int main(int argc, const char * argv[]) {
    Solution gua;
    vector<string> rtn;
    int turnon;
    
    rtn = gua.readBinaryWatch(turnon = 1);
    cout << rtn << endl;
    return 0;
}

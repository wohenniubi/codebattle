
#include <iostream>
#include <unordered_map>

using namespace std;

class Solution {
public:
    //Runtime: 32 ms, faster than 29.50%
    //Memory Usage: 8.9 MB, less than 12.99%
    bool checkInclusion(string s1, string s2) {
        // 和76题很像，只不过这里的permutation意味着不能有中断（不同的char）或者溢出（多余的char）
        unordered_map<char,int> mapS1, mapS2;
        for (char x : s1) mapS1[x]++;
        
        int lhs = 0, valid = 0;// 都把慢索引设置为0
        for (int i = 0; i < s2.size(); ++i) {
            char x = s2[i];
            mapS2[x]++;
            // 加入之后的操作，如果i这个位置的x不在s1里面，直接导致mapS2清空
            //if (mapS1.count(x) == 0 || mapS1[x] < mapS2[x]) {
            if (mapS1.count(x) == 0) { // 把存在于mapS1中的x留到后面处理
                mapS2.clear();
                lhs = i+1;
                valid = 0;// 大意了啊，别忘记清空valid
                continue;
            }
            
            // 现在x存在于mapS1中，mapS1[x] >= mapS2[x]
            if (mapS1[x] == mapS2[x]) valid++;
            
            // 现在判断是否需要控制左边界
            if (valid == mapS1.size()) {
                return true;
            }
            
            // 如果比目标字符串多，此时要减少滑动窗，，让lhs右滑
            while (mapS2[x] > mapS1[x]) {
                char tmp = s2[lhs];
                // 能够运行到这里，说明tmp必然是在s1中的
                if (mapS1[tmp] == mapS2[tmp]) valid--;
                
                mapS2[tmp]--;
                lhs++;
            }
        }
        
        // 跳出说明没有找到s1
        return false;
    }
};

int main(int argc, const char * argv[]) {
    Solution gua;
    string s1, s2;
    bool rtn;

    rtn = gua.checkInclusion(s1="adc", s2="dcda");
    cout << "expect value = 1, actual value = " << rtn << endl;
    
    rtn = gua.checkInclusion(s1="ab", s2="eidboaoo");
    cout << "expect value = 0, actual value = " << rtn << endl;
    return 0;
}


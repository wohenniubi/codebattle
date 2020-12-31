
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    //Runtime: 20 ms, faster than 22.91%
    //Memory Usage: 15.7 MB, less than 65.94%
    bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
        // 貌似我看出来怎么做了，借助一个stack存push数组，同时移动pop数组的指针
        int len = pushed.size();
        //bool rtn = true;
        vector<int> st;
        
        // pospo是popped的index
        int pS = 0, pD = 0;
        // 好丢人第一次居然没有做出来
        while (pS < len || st.size()) {
            if (st.empty()) {
                // 必然是pS小于len，否则跳出while循环
                st.push_back(pushed[pS++]);
                continue;//交给下一次循环
            }
            
            // 下面就是st与popped数组的判断了，一定有值
            if (st.back() == popped[pD]) {
                pD++;
                st.pop_back();
                //pS = (pS < len)? pS+1: pS;
            } else {
                if (pS < len) {
                    st.push_back(pushed[pS++]);
                } else {
                    break;
                }
            }
        }
                
        return pS == pD;
        // 测试一下
        // case1: pushed = [1,2,3,4,5], popped = [4,5,3,2,1]
        // INI: pS = 0, pD = 0, st = []
        // WL0: st = [] -> st = 1, pS=1
        // WL1: st.back():1 != 4 -> st = 1,2, pS=2
        // WL2: st.back():2 != 4 -> st = 1,2,3, pS=3
        // WL3: st.back():3 != 4 -> st = 1,2,3,4, pS=4
        // WL4: st.back():4 == 4 -> st = 1,2,3, pD = 1
        // WL5: st.back():3 != 5 -> st = 1,2,3,5, pS=5
        // WL6: st.back():5 == 5 -> st = 1,2,3, pD = 2
        // WL7: st.back():3 == 3 -> st = 1,2, pD = 3
        // WL8: st.back():2 == 2 -> st = 1, pD = 4
        // WL9: st.back():1 == 1 -> st = [], pD = 5, break
        // return 5 == 5: true
        
        // cas2: pushed = [1,2,3,4,5], popped = [4,3,5,1,2]
        // INI: pS = 0, pD = 0, st = []
        // WL0: st = [] -> st = 1, pS = 1
        // WL1: st.back():1 != 4 -> st = 1,2, pS=2
        // WL2: st.back():2 != 4 -> st = 1,2,3, pS=3
        // WL3: st.back():3 != 4 -> st = 1,2,3,4, pS=4
        // WL4: st.back():4 == 4 -> st = 1,2,3, pD=1
        // WL5: st.back():3 == 3 -> st = 1,2, pD=2
        // WL6: st.back():2 != 5 -> st = 1,2,5, pS=5
        // WL7: st.back():5 == 5 -> st = 1,2, pD=3
        // WL8: st.back():2 != 1 -> break
        // return 5 == 3: false
    }
};

int main(int argc, const char * argv[]) {
    Solution gua;
    bool rtn;
    vector<int> pushed, popped;
    rtn = gua.validateStackSequences(pushed={1,2,3,4,5}, popped={4,5,3,2,1});
    cout << "expect value = 1, actual value = " << rtn << endl;
    
    rtn = gua.validateStackSequences(pushed={1,2,3,4,5}, popped={4,3,5,1,2});
    cout << "expect value = 0, actual value = " << rtn << endl;
    
    return 0;
}

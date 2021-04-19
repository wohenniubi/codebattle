
#include <vector>
#include <iostream>
#include <numeric>

using namespace std;

class Solution {
public:
    
    int dfs(string &s, int &pos) {
        int size = s.size();
        // 返回条件TODO
        
        char prev = '+';
        int sum = 0;
        vector<int> st{0};
        while (pos < size) { // while循环的好处是参数少，参数的增加都考自己，逻辑复杂时利于简化操作
        // for (int i = pos; i < size; ++i) {
        //     pos++;//处理完了一个字符
            char c = s[pos];//s[i];
            
            // 首先是找出数字和计算加减
            if (isdigit(c)) {
                sum = sum * 10 + (s[pos]-'0');
            }
            
            if ('(' == c) {
                // 1 + 3*(2+1)
                // sum = dfs(s, pos); // 前提是不会出现3(3+1)这种情况，那么在遇到(之前的sum一定为0，因为(前面必然有个操作符号
                ++pos;//跳过(
                sum = dfs(s, pos); // 前提是不会出现3(3+1)这种情况，那么在遇到(之前的sum一定为0，因为(前面必然有个操作符号
                // st.push_back(sum); 
                // 此时prev保留着之前的操作符，所以可以继续进入下面的if分支
            }
            
            // 还有小细节是空格，和 i == size-1的处理TODO
            // 对于空格，如果允许它进入这个if分支会导致sum清零，但是如果它是最后一个字符时又该进入，所以稍加修改判断条件，跳过空格
            if ((!isdigit(c) && ' ' != c) || pos == size-1) { //最后一位时等价于一个操作符 
                if ('+' == prev || '-' == prev) {
                    if ('+' == prev)
                        st.push_back(sum);
                    else
                        st.push_back(-sum);
                }// 现在加减号处理完了
                else if ('*' == prev || '/' == prev) {
                    // 要使用st.back() 与当前值进行计算; 这是乘除法优先级的所在
                    if ('*' == prev)
                        st.back() *= sum;
                    else
                        st.back() /= sum;
                    // sum = 0;
                    // // prev = (' ' == c)? '+': c; // 把空格当作人畜无害的+
                    // prev = c;// 把空格当作人畜无害的+
                } // 现在乘除号处理完了
                
                // 由于不可避免的会让(进入prev，此时sum为0，其实没有什么操作；但是可以把prev顺便更新为c，所以要抽出来放在外面
                sum = 0;
                // prev = (' ' == c)? '+': c; // 把空格当作人畜无害的+
                prev = c;// 把空格当作人畜无害的+
                
                // else if ('(' == c) { 已经打算这里增加对(的处理，不过觉得放到这里是不明智的
                // if (')' == c) // 不应该在这里跳出
                //     break;// 此时所有操作都做了安排，梦该醒了，跳出吧
            }
            
            if (')' == c)
                break;// 此时所有操作都做了安排，梦该醒了，跳出吧
            ++pos; //把pos更新放在)后面，这样pos始终停在)处，下一个while循环不会漏掉后面可能的字符
        }
            
        //一边计算一边解析的操作有点难，所以还是安心使用遍历
        return accumulate(st.begin(), st.end(), 0);//st_back()
    }
    
    int calculate(string s) {
        // int size = s.size();
        int size = 0;
        
        // 这是典型的问题，逐步完善设计：先考虑只有加减，再考虑乘除，最后是括号
        // 括号肯定是递归，所以先写个递归函数，由pos控制问题规模逐渐变小，即开始处理时的位置
        return dfs(s, size);
    }
};

int main() {
  Solution gua;
  int rtn;
  string s;
  rtn = gua.calculate(s = "1 + 1");
  cout << "expect value = 2, actual value = " << rtn << endl;

  rtn = gua.calculate(s = " 2-1 + 2");
  cout << "expect value = 3, actual value = " << rtn << endl;

  rtn = gua.calculate(s = "(1+(4+5+2)-3)+(6+8)");
  cout << "expect value = 23, actual value = " << rtn << endl;

  return 0;
}



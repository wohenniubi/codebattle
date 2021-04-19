
#include <iostream>
#include <vector>

using namespace std;

typedef unsigned __int128 uint128_t;

class Solution {
public:
    //Runtime: 24 ms, faster than 18.01%
    //Memory Usage: 26 MB, less than 11.18%
    int numDistinct(string s, string t) {
        //是DP问题;
        int lenS = s.size(), lenT = t.size();
        
        // vector<vector<int>> dp(lenT+1, vector<int>(lenS+1)); // 尼玛题目说好了uint32可以装下的，为啥不得行？
        vector<vector<uint128_t>> dp(lenT+1, vector<uint128_t>(lenS+1));
        for (int i = 0; i <= lenS; ++i) {
            dp[0][i] = 1; // t是空集，s里面有且仅有空集可以与之匹配，所以等于1
        }
        
        // 现在开始计算dp，dp[i][j]的含义是t[1,i]和s[1,j]
        // 状态如何转移，要看t[i]和s[j]的关系
        for (int i = 1; i <= lenT; ++i) {
            for (int j = 1; j <= lenS; ++j) {
                if (t[i-1] == s[j-1]) {
                    // 那么构成subsequence t[1...i]的个数包括两部分，包含s[j]和不包含s[j]的情况
                    dp[i][j] = dp[i-1][j-1] + dp[i][j-1];
                } else {
                    dp[i][j] = dp[i][j-1];// 那么只能削减s的长度了；之所以不削减t的长度，那是因为要匹配t呀
                }
            }
        }
        
        return dp[lenT][lenS];
    }
};

int main(int argc, const char * argv[]) {
    // insert code here...
    Solution gua;
    int rtn;
    string s, t;
    rtn = gua.numDistinct(s="rabbbit", t="rabbit");
    cout << "expect value = 3, actual value = " << rtn << endl;

    rtn = gua.numDistinct(s="babgbag", t="bag");
    cout << "expect value = 5, actual value = " << rtn << endl;
    
    s = "xslledayhxhadmctrliaxqpokyezcfhzaskeykchkmhpyjipxtsuljkwkovmvelvwxzwieeuqnjozrfwmzsylcwvsthnxujvrkszqwtglewkycikdaiocglwzukwovsghkhyidevhbgffoqkpabthmqihcfxxzdejletqjoxmwftlxfcxgxgvpperwbqvhxgsbbkmphyomtbjzdjhcrcsggleiczpbfjcgtpycpmrjnckslrwduqlccqmgrdhxolfjafmsrfdghnatexyanldrdpxvvgujsztuffoymrfteholgonuaqndinadtumnuhkboyzaqguwqijwxxszngextfcozpetyownmyneehdwqmtpjloztswmzzdzqhuoxrblppqvyvsqhnhryvqsqogpnlqfulurexdtovqpqkfxxnqykgscxaskmksivoazlducanrqxynxlgvwonalpsyddqmaemcrrwvrjmjjnygyebwtqxehrclwsxzylbqexnxjcgspeynlbmetlkacnnbhmaizbadynajpibepbuacggxrqavfnwpcwxbzxfymhjcslghmajrirqzjqxpgtgisfjreqrqabssobbadmtmdknmakdigjqyqcruujlwmfoagrckdwyiglviyyrekjealvvigiesnvuumxgsveadrxlpwetioxibtdjblowblqvzpbrmhupyrdophjxvhgzclidzybajuxllacyhyphssvhcffxonysahvzhzbttyeeyiefhunbokiqrpqfcoxdxvefugapeevdoakxwzykmhbdytjbhigffkmbqmqxsoaiomgmmgwapzdosorcxxhejvgajyzdmzlcntqbapbpofdjtulstuzdrffafedufqwsknumcxbschdybosxkrabyfdejgyozwillcxpcaiehlelczioskqtptzaczobvyojdlyflilvwqgyrqmjaeepydrcchfyftjighntqzoo";
    t = "rwmimatmhydhbujebqehjprrwfkoebcxxqfktayaaeheys";
    rtn = gua.numDistinct(s, t);
    cout << "expect value = 543744000, actual value = " << rtn << endl;
    
    return 0;
}

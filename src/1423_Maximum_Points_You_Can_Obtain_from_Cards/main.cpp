#include <vector>
#include <numeric> // accumulate

using namespace std;

class Solution {
public:
    //Runtime: 112 ms, 77.87%
    //Memory Usage: 42.7 MB, 91.74%
    int maxScore(vector<int>& cardPoints, int k) {
        // 这道题好贱，我以为是dp，想了半天这个数据范围太大了，绝对撑爆
        // 结果错过了一个关键的细节，这些去掉的数字一定都是连续的！！！因此可以简化为滑动窗
        
        int len = cardPoints.size();
        // sumL记录左边k个数的sum，每次减少一个，直到0个，所以一共有k+1个状态；
        // 这里初始化为全部k个数的情况
        int sumL = accumulate(cardPoints.begin(), cardPoints.begin()+k, 0);
        
        // [1,2,3,4,5] k = 2, 那么只可能由以下三种情况，那么就是逐个遍历了
        // 1,2 | 3, 4, 5
        // 1 | 2, 3, 4 | 5
        // 1,2,3 | 4, 5
        int rtn = sumL, sumR = 0;
        
        // 开始k+1个状态中k个状态的更新
        // 因为题目说了k会小于等于len，所以这里不做合法性检测
        for (int i = k-1; i>=0 ; --i) {
            sumL -= cardPoints[i];// 比如i=k-1时，去掉第k-1个数
            //sumR += cardPoints[len-i-k];
            sumR += cardPoints[len-(k-i)];
            // i=0时右侧加上len-k这个数，i=1时右侧加上len-k+1这个树
            // 后者凑成同样的形式len-(k+1)，因此推测公式为len-(k-i)，再带入i=k-1验证一下，
            // 此时右侧加上第len-1个数，符合条件，赞！
            rtn = max(rtn, sumL + sumR);
        }
        
        return rtn;
    }
};

int main(int argc, const char * argv[]) {
    Solution gua;
    int rtn, k;
    vector<int> cardPoints;
    rtn = gua.maxScore(cardPoints = {1,79,80,1,1,1,200,1}, k = 3);
    cout << "expect value = 202, actual value = " << rtn << endl;

    rtn = gua.maxScore(cardPoints = {1,100,1}, k = 1);
    cout << "expect value = 1, actual value = " << rtn << endl;

    rtn = gua.maxScore(cardPoints = {9,7,7,9,7,7,9}, k = 7);
    cout << "expect value = 55, actual value = " << rtn << endl;
    return 0;
}


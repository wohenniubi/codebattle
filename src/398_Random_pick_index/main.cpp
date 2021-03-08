#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution1 {
public:
    // 这种思路下的时间复杂度为O(1), 空间复杂度为O(n)
    unordered_map<int, vector<int>> helper;

    Solution1(vector<int> & nums) {
        int len = nums.size();
        for (int i = 0; i < len; ++i) {
            helper[nums[i]].push_back(i);
        }
    }
    
    int pick(int target) {
        auto iter = helper.find(target);
        int val = rand() % ((iter->second).size());
        return iter->second[val];
    }
};

// 网上的解答, 采用的是水塘采用reservoir sampling
// 这里的水塘宽度为1, 因此在操作中省略, 然后结合本题, 遍历时的index要另外计算,
// 即val = target时才认为是index++, 时间复杂度O(n), 空间复杂度O(n)
class Solution {
public:
    vector<int> data;

    Solution(vector<int> & nums) {
        data = nums;
    }
    
    int pick(int target) {
        int cnt = 1, ret = -1;
        for (int i = 0; i < data.size(); ++i) {
            // 当val不等于target时, 都continue, 等价于过滤掉
            if (data[i] != target)
                continue;
            // 一般情况下的水塘采样是与水塘宽度m进行比较. 例如rand()%cnt < m;
            // 但是由于本题水塘宽度m=1, rand%cnt < 1就简化为rand%cnt == 0
            // 然后根据条件记录此时的index, 作为返回值; 
            // 另外注意, cnt是从水塘size以外开始的, 所以本题中cnt初始化为0, 
            // 然后在rand()%cnt之前 ++, 或者先初始化为1, 然后在rand()%cnt之后++
            if (rand()%cnt == 0) {
                ret = i;
            }
            ++cnt;// 切记切记不要忘记更新cnt了, 要不然就不是random了
        }
        return ret;
    }
};

int main() {
    int ret, target;
    vector<int> num1 = {1,2,3,3,3};
    Solution gua(num1);
    ret = gua.pick(target=3);
    cout << "rand value = " << ret << endl;
    ret = gua.pick(target=3);
    cout << "rand value = " << ret << endl;
    ret = gua.pick(target=3);
    cout << "rand value = " << ret << endl;
    return 0;
}


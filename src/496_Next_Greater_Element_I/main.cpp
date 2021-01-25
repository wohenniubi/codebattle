
#include <iostream>
#include <vector>
#include <stack>
#include <unordered_map>

using namespace std;

class Solution {
public:
    // 这道题前搞懂题意：是指要从nums2里面nums1[i]出现的位置向右找一个更大的数
    //Runtime: 4 ms, faster than 98.93%
    //Memory Usage: 8.8 MB, less than 83.27%
    // 方法2 借助了单调栈，同时使用了哈希表，这种办法很难想到，被nums1迷惑了，
    // 其实原理就是在nums2里面找到比当前位置大的值，然后使用哈希表把这些值记录下来而已
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        stack<int> s;
        unordered_map<int,int> dict;
        
        for (auto val : nums2) {
            while(s.size() && val > s.top()) {
                // pop之前保存一下结果，说明这就是s.top()右边第一个比它大的数
                dict[s.top()] = val;
                
                // 这是基本模版，把中间不断pop，因为对于最后结果没有帮助
                s.pop();
            }// 跳出循环时s为空，或者比s最后一位小
            s.push(val);
        }
        vector<int> rtn;
        for (auto val : nums1) {
            // 如果某个值仅仅被push到s里面，但是并没有被写入dict，说明后面找不到一个大于它的值，按题意填入-1
            rtn.push_back((dict.count(val)? dict[val] : -1));
        }
        
        // 然后没想到更好的办法，不过至少需要一些查找表，这里使用红黑树
//        map<int,int> valToPos;
//        vector<int> rtn;
//        for (int i = 0; i < nums2.size(); ++i) {
//            valToPos[nums2[i]] = i;
//        }
//        for (int val : nums1) {
//            auto iter = valToPos.find(val);
//            // 因为nums1是nums2的subset，所以iter不会等于valToPos.end()
//            auto [key, pos] = *iter;
//            if (pos == nums2.size()-1) {
//                rtn.push_back(-1);
//                continue;
//            }
//            bool isLarger = false;
//            while (++iter != end(valToPos)) {
//                if (iter->second > pos) {
//                    isLarger = true;
//                    break;
//                }
//            }
//            rtn.push_back(isLarger? (iter->first): -1);
//        }
        
        return rtn;
    }
    
    // 方法1：暴力法，先找到nums2中nums1[i]的位置，然后从这个位置向右找大于它的值
    //Runtime: 4 ms, faster than 98.93%
    //Memory Usage: 8.5 MB, less than 97.93%
    vector<int> nextGreaterElement1(vector<int>& nums1, vector<int>& nums2) {
        vector<int> rtn;
        for (auto val : nums1) {
            int i = 0;
            auto iter = find(nums2.begin(), nums2.end(), val);
            while (++iter != end(nums2)) {
                if (*iter > val) break;
            }
            rtn.push_back((iter == end(nums2))? -1 : *iter);
        }
        return rtn;
    }
};

ostream & operator<<(ostream &os, vector<int> rtn) {
    os << "[";
    for (auto val : rtn) os << val << ",";
    os << "]";
    return os;
}

int main(int argc, const char * argv[]) {
    Solution gua;
    vector<int> nums1, nums2, rtn;
    rtn = gua.nextGreaterElement(nums1={4,1,2}, nums2={1,3,4,2});
    cout << "expect result = " << vector<int>{-1,3,-1} << ", actual result = " << rtn << endl;
    
    rtn = gua.nextGreaterElement(nums1={2,4}, nums2={1,2,3,4});
    cout << "expect result = " << vector<int>{3,-1} << ", actual result = " << rtn << endl;
    
    return 0;
}

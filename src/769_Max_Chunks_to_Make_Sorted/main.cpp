
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    //Runtime: 0 ms, faster than 100.00%
    //Memory Usage: 7.2 MB, less than 71.60%
    // 采用greedy的做法，适用于没有重复字符的情况
    int maxChunksToSorted(vector<int>& arr) {
        int rtn = 0;
        
        // 从每个位置向后扫描，看当前位置的值需要被放置在哪个index，这里相当于直接用到了sorted之后[0,n-1]数组的特性，值即index
        for (int i = 0; i < arr.size(); ++i) {
            // 从左到右遍历，获得当前位置的值arr[i]，那么分割块必须延伸到与这个值相等的index处
            // sort之后，值即是index，因此[i,cur]这个区间里的所有值都应该包含在一个分段里面，否则sort之后不能被放到正确的位置
            int cur = arr[i];// 这个值就是index的上限了
            int j = i+1;
            
            // 然后再要逐一检查[i+1,cur]这里的所有值是不是确定都包含在cur里面，如果不是的话，需要扩大分段的右边界
            for (; j <= cur; ++j) {
                // 在不断的延伸过程中，如果发现了超过cur的值，说明这个分段含有某个值arr[j]
                // 那么这个分段的右边界也必须延伸到与arr[j]值相等的index处，也即是cur的上限被修改了
                cur = max(cur, arr[j]);
                if (cur >= arr.back())
                    return rtn + 1;// 如果上限超过了最后一个数，那么这个分段必然包含到最后，那么提前返回
                
                // 另一种写法也可以，时间复杂度一样，不过稍微慢了一点，可能是因为没有尽可能扩大cur，没有提前返回
                //Runtime: 4 ms, faster than 9.77%
                //Memory Usage: 7.1 MB, less than 71.60%
//                 if (arr[j] <= cur) continue;
//
//                 // 修改cur，扩大分段的右边界
//                 // cur = arr[j]; 大意了啊，扩大分段需要max
//                 cur = max(cur, arr[j]);
//
//                 // 这里有个剪支操作，如果cur已经能够扩张到最后一个值，那么直接跳出，不用操作了
//                 if (cur > arr.back()) { // 因为没有重复，所以可以不用等号
//                     // break; 大意了啊，此时可以直接返回了
//                     return rtn + 1;
//                 }
            }
            
            // 当执行完内部for loop之后（j等于cur+1才能跳出内部循环），[i,cur]之间的数都可以包含到一个分段中，那么这个分段结束
            i = j-1; //然后我们希望i从cur+1这个index开始继续遍历，但是为了与外部for循环的++i匹配，故这里减1
            ++rtn;
        }
        
        return rtn;
    }
};

int main(int argc, const char * argv[]) {
    // insert code here...
    Solution gua;
    vector<int> arr;
    int rtn;
    
    rtn = gua.maxChunksToSorted(arr = {2, 0, 1, 4, 3});
    cout << "expect value = 2, actual value = " << rtn << endl;

    rtn = gua.maxChunksToSorted(arr = {1, 2, 3, 4, 5, 0});
    cout << "expect value = 1, actual value = " << rtn << endl;

    return 0;
}

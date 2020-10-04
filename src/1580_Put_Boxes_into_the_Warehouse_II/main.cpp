
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    // 以下方式不work哦
    int maxBoxesInWarehouse1(vector<int>& boxes, vector<int>& warehouse) {
        // 由于boxes可以rerange，且可以从两边进入的话，这道题貌似直接sort就可以了? ——没那么简单，room不能sort
        int len_w = warehouse.size(), len_b = boxes.size();
        sort(boxes.begin(), boxes.end());
        //sort(warehourse.begin(), warehourse.end()); 笔误啊笔误啊
        sort(warehouse.begin(), warehouse.end());
        
        // 然后是greedy做法，尽量把boxes小的先塞入小的room
        int rtn = 0, pos = 0;
        for (int i = 0; i < len_b; ++i) {
            while (pos < len_w && warehouse[pos] < boxes[i]) {
                pos++;
            }// 这个while循环是为了找到第一个可以装下box的room
            
            if (pos >= len_w) {
                return rtn;// 仓库满了，没有可用的房间了
            } else {
                rtn++;
                pos++;// 可用房间数减少1
            }
        }
        return rtn;
    }
    
    // greedy做法， 采用和leetcode 1564一样的思路：因为boxes可以rearrange，而且从左到右、从右到左都可以，
    // 所以就“尽力”的放，比如把最大的放在最近的room里面，这样小的box可以塞进更远，更小的房间
    //Runtime: 412 ms, faster than 58.74% 
    //Memory Usage: 60.3 MB, less than 75.34%
    int maxBoxesInWarehouse(vector<int>& boxes, vector<int>& warehouse) {
        //sort(boxes.rbegin(), boxes.rend());// 也可以采用从后往前按照由小到大的默认顺序sort，很巧妙的办法
        sort(boxes.begin(), boxes.end(),greater<int>());
        
        int left = 0, right = warehouse.size()-1, rtn = 0;
        for (auto box : boxes) {
            // 因为box的大小是变小的，因此这里先从左边或者从右边都不影响。例如：
            // 如果先放入最左边，假如
            //      (1) 此时最右边比左边大，那么之后的box放入左右都没有关系；
            //      (2) 若最右边比左边小，那么至少还放了一个到仓库；
            // 如果最开始不能放入左边，会检查右边，所以也不会漏掉放入仓库的可能性
            // 反之先判断放入最右边也是类似
            if (warehouse[left] >= box) {
                rtn++;
                left++;
            } else if (warehouse[right] >= box) {
                rtn++;
                right--;
            }// 如果左右都放不进去，那这个box就扔掉，哇咔咔
            // 大意了大意了，此时需要判断左边和右边是不是相遇了
            if (left > right)
                break;// left和right之间是可用的空间，这种情况下仓库已经没有空间了
        }
        return rtn;
    }
};

int main(int argc, const char * argv[]) {
    Solution gua;
    int rtn;
    vector<int> boxes, warehouse;
    boxes = {5,21,11,2,5,8,30,8,35,19,28,16,3,5,12,7,30,24,18};
    warehouse = {31,18,9,20,13,14,16,29,34,13,18,21};
    rtn = gua.maxBoxesInWarehouse(boxes, warehouse);
    cout << "expect value = 12, actual value = " << rtn << endl;
    
    rtn = gua.maxBoxesInWarehouse(boxes={4,5,6,2}, warehouse={3,2,6,3,3,7});
    cout << "expect value = 2, actual value = " << rtn << endl;
    return 0;
}

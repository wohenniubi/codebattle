
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    //Runtime: 396 ms, faster than 44.20%
    //Memory Usage: 61.6 MB, less than 32.32%
    int maxBoxesInWarehouse(vector<int>& boxes, vector<int>& warehouse) {
        // 基本思路greedy：因为没有说箱子的价值，那就把所有的箱子高度排个序，左到右是由大到小，
        // 然后再从货仓的从右往左判断是否可以塞得进去
        int rtn = 0, size = warehouse.size()-1;
        sort(boxes.begin(), boxes.end());// 默认sort是由小到大，不过正好for loop遍历由小到大，所及就不用less<int>进行排序了
        
        vector<int> rooms = warehouse; // 需要增加一步操作，将warehouse向左削平
        //for (int i = 1; i < size; ++i) rooms[i] = min(rooms[i-1], rooms[i]); 别想当然的改代码啊...
        for (int i = 1; i < warehouse.size(); ++i) rooms[i] = min(rooms[i-1], rooms[i]);
        
        for (int i = 0; i < boxes.size(); ++i) {
            //while (size >= 0 && warehouse[size] < boxes[i]) {
            while (size >= 0 && rooms[size] < boxes[i]) {
                size--;
            }
            // 跳出对warehouse的while循环时，表明找到了一个可以放入box的room，或者是warehouse满了
            if (size < 0) {
                return rtn;// warehouse满啦
            } else {
                // 此时size>=0
                rtn++;
                size--; //warehouse房间减少1个
            }
        }
        
        return rtn;
    }
};

int main(int argc, const char * argv[]) {
    Solution gua;
    int rtn;
    vector<int> boxes, warehouse;
    rtn = gua.maxBoxesInWarehouse(boxes={2,5,5,2}, warehouse={6,1,1,2,3,4,3,7,5,6,2,8,8,5});
    cout << "expect value = 1; actual value = " << rtn << endl;
    
    rtn = gua.maxBoxesInWarehouse(boxes={1,2,3}, warehouse={1,2,3,4});
    cout << "expect value = 1; actual value = " << rtn << endl;
    
    return 0;
}

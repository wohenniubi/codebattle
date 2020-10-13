
// #include "stdafx.h"
#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
	// 再做时怎么搞不懂了... dp解法, 需要两个历史数组
	int wiggleMaxLength(vector<int>& nums) {
		int p = 1, q = 1, n = nums.size();
		vector<int> p_gdb(nums.size(),1);// p表示到i为上升的序列的最大长度, 初始化为1说得通, 自己本身是个trivial解
		vector<int> q_gdb(nums.size(),1);// q表示到i为下降的序列的最大长度, 初始化为1说得通, 自己本身是个trivial解

		vector<int> p_bag{p}, q_bag{q}; //仅仅用于debug
		// 由于可以去掉一些number, 所以取上一个或升或减的序列的长度来更新当前的序列长度
		for (int i = 1; i < n; ++i) {
			if (nums[i] > nums[i - 1]) {
				p = q + 1;
				q_gdb[i] = q_gdb[i - 1];
				p_gdb[i] = q_gdb[i - 1] + 1;
				p_bag.push_back(p); q_bag.push_back(q);
			}
			else if (nums[i] < nums[i - 1]) {
				q = p + 1; 
				p_gdb[i] = p_gdb[i - 1];
				q_gdb[i] = p_gdb[i - 1] + 1;
				p_bag.push_back(p); q_bag.push_back(q);
			} else { // 不要大意啊!!!!! 如果使用的是两个dp数组, 当没有操作时需要传递值
				// 但是这一步可以被省略, 因为如果将两个dp数组简化为两个变量时, 不更新就表示传递值
				p_gdb[i] = p_gdb[i - 1];
				q_gdb[i] = q_gdb[i - 1];
			}
		}

		// for (auto i : p_gdb) cout << i << " "; cout << endl;
		// for (auto i : p_bag) cout << i << " "; cout << endl;
		// cout << endl;
		// for (auto i : q_gdb) cout << i << " "; cout << endl;
		// for (auto i : q_bag) cout << i << " "; cout << endl;
		return min(n, max(p, q));//最后这个min只是为了应对空[]的情况
	}
};

int main()
{
	Solution gua;
	int  rtn;
	vector<int> test3;
	rtn = gua.wiggleMaxLength(test3);
	cout << "expect value = 0, actual value = " << rtn << endl;

	vector<int> test2{ 51,226,208,165,202,286,190,212,219,271,36,245,20,238,238,89,105,66,73,9,254,206,221,237,203,33,249,253,150,102,57,249,203,10,123,178,85,203,35,276,129,116,37,163,99,142,187,249,134,77,217,298,29,127,174,115,122,178,12,80,122,76,16,41,115,84,104,121,127,40,287,129,9,172,112,51,40,135,205,53,259,196,248,5,123,184,209,130,271,42,18,143,24,101,10,273,252,50,173,80,119,129,45,257,299,78,278,78,190,215,284,129,200,232,103,97,167,120,49,298,141,146,154,233,214,196,244,50,110,48,152,82,226,26,254,276,292,286,215,56,128,122,82,241,222,12,272,192,224,136,116,70,39,207,295,49,194,90,210,123,271,18,276,87,177,240,276,33,155,200,51,6,212,36,149,202,48,114,58,91,83,221,175,148,278,300,284,86,191,95,77,215,113,257,153,135,217,76,85,269,126,194,199,195,20,204,194,50,220,228,90,221,256,87,157,246,74,156,9,196,16,259,234,79,31,206,148,12,223,151,96,229,165,9,144,26,255,201,33,89,145,155,1,204,37,107,80,212,88,186,254,9,158,180,24,45,158,100,52,131,71,174,229,236,296,299,184,168,41,45,76,68,122,85,292,238,293,179,143,128,47,87,267,53,187,76,292,0,160,70,172,292,9,64,156,153,26,145,196,222 };
	rtn = gua.wiggleMaxLength(test2);
	cout << "expect value = 202, actual value = " << rtn << endl;

	vector<int> test1{ 1,17,5,10,13,15,10,5,16,8 };
	rtn = gua.wiggleMaxLength(test1);
	cout << "expect value = 7, actual value = " << rtn << endl;

    return 0;
}


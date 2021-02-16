#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
	// BFS based method, rst is used as queue, totally 2^n subsets
	vector<vector<int>> subsets(vector<int>& nums) {
		vector<vector<int>> rst;
		if (nums.empty()) return rst;

		rst.push_back(vector<int>());
		// only loop totally size() position;
		for (int i = 0; i < nums.size(); ++i) {
			int size = rst.size();
			// only loop totally size rounds;
			// in essence, this will double the size of rst;
			// thus, finally the size of rst is 2^n
			for (int j = 0; j < size; ++j) {
				rst.push_back(rst[j]);
				rst.back().push_back(nums[i]);
			}
		}
		return rst;
	}

	vector<vector<int>> result;
	void helper(vector<int>& nums, int start, vector<int>& tmpbag) {
		for (int cnt = start; cnt < nums.size(); ++cnt) {
			tmpbag.push_back(nums[cnt]);
			helper(nums, cnt + 1, tmpbag);
			result.push_back(tmpbag);
			tmpbag.pop_back();
		}
	}
	// recursively method, treat it as DFS
	vector<vector<int>> subsets2(vector<int>& nums) {
		vector<int> tmpbag;
		result.push_back(tmpbag);
		helper(nums, 0, tmpbag);
		return result;
	}

	void getSubSets(vector<int>& nums, int pos, vector<int> &out, vector<vector<int>> &rst) {
		// deal with the end case
		if (pos == nums.size()) {
			rst.push_back(out);
			return;
		}

		for (int i = pos; i < nums.size(); ++i) {
			out.push_back(nums[i]);
			getSubSets(nums, pos+1, out, rst);
			out.pop_back();// do not choose the current val
		}
	}

	// recursively method, treat it as DFS
	vector<vector<int>> subsets3(vector<int>& nums) {
		vector<vector<int>> rst;
		vector<int> out;
		rst.push_back(vector<int>());
		getSubSets(nums, 0, out, rst);
		return rst;
	}
};

ostream & operator<< (ostream &os, vector<vector<int>> &rtn) {
  os << "[";
  for (auto & val : rtn) {
    os << "[";
    for (auto i : val) {
      os << i << ", ";
    }
    os << "], ";
  }

  os << "]";
  return os;
}

int main() {
	Solution gua;
	vector<int> nums{ 1,2,3 };
	vector<vector<int>> rst = gua.subsets(nums);
  cout << rst << endl;

  return 0;
}


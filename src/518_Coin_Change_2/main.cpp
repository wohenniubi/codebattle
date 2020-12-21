#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
	int change(int amount, vector<int>& coins) {
		if (amount == 0 || coins.empty()) return 0;

		// dp array keep the total combinations of a certain value;
		vector<vector<int>> dp(coins.size()+1, vector<int>(amount + 1));
		dp[0][0] = 1;
		for (int j = 1; j <= coins.size(); ++j) {
			dp[j][0] = 1;//otherwise there will be all zeros
			for (int i = 1; i <= amount; ++i) {
				dp[j][i] = dp[j - 1][i] + (i >= coins[j - 1] ? dp[j][i - coins[j - 1]] : 0);
			}
		}

		//for (int i = 1; i <= amount; ++i) {
		//	tmpSum = 0;
		//	// sum up the combinations of each branch, amount i-j 
		//	for (auto j : coins) {
		//		//tmpSum += dp[i-j];
		//		tmpSum += (i >= j) ? dp[i - j] : 0;
		//	}
		//	dp[i] = tmpSum;
		//}
		return dp.back().back();
	}
};

int main()
{
	Solution gua;
	int amount;
	int rst;
	vector<int> coins1 = { 2 };
	amount = 3;
	//rst = gua.change(amount, coins1);
	//cout << "rst = " << rst << endl;

	vector<int> coins2 = { 1,2,5 };
	amount = 5;
	rst = gua.change(amount, coins2);
	cout << "rst = " << rst << endl;


    return 0;
}


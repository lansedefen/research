#include<vector>
#include<string>
#include<iostream>

using namespace std;

int MaxValidNum(int num, int k) {
	cout << "num:" << num << endl;
	int max_bit = sizeof(num) * 8 - 1;
	cout << "max_bit:" << max_bit << endl;
	vector<vector<int> > dp(max_bit , vector<int> (k + 1, 0));
    for(int i = 0; i < k - 1; i++) {
		dp[0][i] = 1;
	}
	
	for(int i = 1; i< dp.size();i++) {
		for(int j = 1; j < dp[i].size();j++)	{
			if (j <= i + 1) {
				dp[i][j] = dp[i-1][j-1] + dp[i-1][j];	
			}
			cout << "i,j:" << i<< "," << j << "   "<<dp[i][j] << "," << endl;
		}			
	}
	int res = 0;
	int bit_one_total = -1;
	while(max_bit > 0) {
		if (num & (1 << max_bit)) {
		   bit_one_total +=1;
		   cout << max_bit << endl; 
		   if (k >=bit_one_total) {
				cout << "max_bit: " << max_bit << endl;
		   		res += dp[max_bit - 1][k- bit_one_total];
				cout << max_bit-1 << "," << k-bit_one_total << "-- "<<(dp[max_bit - 1][k- bit_one_total]) << endl;
			}
		}
		max_bit --;
	}

	cout << bit_one_total << endl;
	if ( k>= bit_one_total && (num & 1) ) {
		res += dp[0][k-bit_one_total];
	}
	cout << "res:" << res << endl;
	return -1;
}

int main() {
	int num = 15;
	int k = 3;
	cout << MaxValidNum(num, k) << endl;
	cout << "xx" << endl;
	return -1;
}

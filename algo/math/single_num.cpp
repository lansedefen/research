#include<vector>
#include<string>
#include<iostream>

using namespace std;

int SingleNum(vector<int>& nums) {
	const int W = sizeof(int) * 8;
	vector<int> count(W, 0);
	cout << count.size() << endl;
	for(int i = 0; i< nums.size() ;i++) {
		for(int j =0; j< W; j++ ) {
			count[j] += (nums[i] >> j) & 1;
			count[j] %=3;
		}
	}
	int result = 0;
	for(int i =0; i< W;i ++) {
		result += (count[i] << i);
	}
	return result;
}

int main() {
	int tmp[] = {-1,-1,-1,2,2,2,4,4};
	vector<int> nums(tmp , tmp + 8);
	int res = SingleNum(nums);
	cout << res << endl;
	return -1;
}

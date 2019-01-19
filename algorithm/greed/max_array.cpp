#include<iostream>
#include<string>
#include<vector>

using namespace std;

int MaxWater(vector<int> nums) {
	int left = 0, right = nums.size() -1;
	int max_water = 0;
	while(left < right) {
		max_water = max(max_water, (right - left) * min(nums[left], nums[right]));
		if (nums[left] < nums[right]) {
			left ++;
		}
		else {
			right --;
		}
	}
	return max_water;
}

int main() {
	vector<int> nums;
	nums.push_back(2);
	nums.push_back(3);
	nums.push_back(1);
	nums.push_back(4);
	int res = MaxWater(nums);
	cout << res << endl;
}

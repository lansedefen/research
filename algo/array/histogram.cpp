#include<string>
#include<vector>
#include<iostream>

using namespace std;

int trap(const vector<int> nums) {
	int max_index = 0;
	for(int i = 0; i< nums.size(); i++) {
		if (nums[i] > nums[max_index]) 
			max_index = i;
	}

	int water = 0; int peak = 0;
	for(int i = 0; i< max_index ; i++) {
		if (nums[i] > peak ) { 
			peak = nums[i];
		} else { 
			water += peak - nums[i];
		}
	}
	peak = 0;
	for (int i = nums.size() -1 ;i > max_index ; i--) {
		if (nums[i] > peak) {
			peak = nums[i];
		} else {
			water += peak - nums[i];	
		}
	
	}
	return water;
}

int main() {
	int tmp[] = {2, 4, 5, 1, 8};
	vector<int> nums(tmp, tmp+ 5);
	int res = trap(nums);
	cout << res << endl;
	return -1;
}

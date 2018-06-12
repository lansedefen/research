#include<iostream>
#include<vector>
using namespace std;

// 去除排序数组中的重复数字
// time: O(n), space: O(1)
int removeDuplicates(vector<int> & nums) {
		if (nums.empty()) return 0; 
		int index = 0;
		for (int i =1; i< nums.size(); i++) {
			if(nums[i] != nums[index]) {
				nums[++index] = nums[i];
			}
		}
		return index + 1;
}

int main() {
	int num_array[] = {1,1,2,3,3,4,5,5};
	vector<int> nums(num_array, num_array + 8);
	removeDuplicates(nums);
	for(int i =0;i < nums.size();i++) {
			cout << nums[i] << endl;
	}
	return -1;
}	

#include<iostream>
#include<vector>

using namespace std;

// 去除排序数组中的重复数字
// time: O(n), space: O(1)
int RemoveDuplicates(vector<int> & nums) {
		if (nums.empty()) 
            return 0; 

		int index = 0;
		for (int i =1; i< nums.size(); i++) {
			if(nums[i] != nums[index]) {
				nums[++index] = nums[i];
			}
		}
		return index + 1;
}

int RemoveKDuplicates(vector<int> & nums) {
		if (nums.empty()) 
            return 0; 

		int index = 1;
		for (int i =2; i< nums.size(); i++) {
			if(nums[i] != nums[index - 1]) {
				nums[++index] = nums[i];
			}
		}
		return index + 1;
}

// 
int RemoveNum(vector<int>& nums, int target) {
    if(nums.empty()) {
        return 0;
    }

    int index = 0;
    for(int i = 0; i< nums.size();i++) {
        if (target != nums[i]) {
            nums[index] = nums[i];
            index++;
        }
    }
    return index ;
}

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

int PartArray(vector<int>& nums) {
    if(nums.size() == 0) {
        return 0;
    }

    int target = nums[0];
    int index = 0;
    int tmp_index = 0;
    for(int i=1; i < nums.size();i++) {
        if (nums[i] <= target) {
            if (index == tmp_index) {
                tmp_index =i;
            }
            swap(nums[i], nums[index]);
            index ++;
        }
    }
    cout << nums[index] << endl <<index << endl;
    swap(nums[tmp_index], nums[index]);
    return -1;
}

int MoveArray(vector<int>& nums) {
    if(nums.size() == 0) {
        return 0;
    }

    int index = 0;
    for(int i=1; i < nums.size();i++) {
        if (nums[i] % 2 == 0) {
            swap(nums[i], nums[index]);
            index ++;
        }
    }
    return -1;
}

int MoveArrayOrder(vector<int>& nums) {
    if(nums.size() == 0) {
        return 0;
    }

    int index = 0;
    for(int i=1; i < nums.size();i++) {
        if (nums[i] % 2 == 0) {
            swap(nums[i], nums[index]);
            index ++;
        }
    }
    return -1;
}

int PrintArray(vector<int>& nums) {
	for(int i =0;i < nums.size();i++) {
			cout << nums[i] << ",";
	}
    cout << endl;
    return -1;
}

int main() {
	int num_array[] = {1,1,1,2,3,3,4,4};
	vector<int> nums(num_array, num_array + 8);
	//RemoveDuplicates(nums);
	RemoveKDuplicates(nums);
    //RemoveNum(nums, 3); 

    //PrintArray(nums);
    //PartArray(nums); 
    //PrintArray(nums);
    //MoveArray(nums);
    PrintArray(nums);
	return -1;
}	

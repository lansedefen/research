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

int PartVector(vector<int>& nums) {
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

int PartVector(vector<int>& nums, int start, int end) {
     int i = start, j = end;
     int base = nums[start];
     while (i < j) {
         cout << "i:" << i << ", j:" << j << endl;
         while (i < j && nums[j] > base) {
             j--;
         }
         nums[i] = nums[j];
 
         cout << "i2:" << i << ", j2:" << j << endl;
         while (i <j && nums[i] <= base) {
             i++;
         }
         nums[j] = nums[i];
         cout << "i3:" << i << ", j3:" << j << endl;
     }
     nums[i] = base;
     return i;
}

int MoveVector(vector<int>& nums) {
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

int MoveVectorOrder(vector<int>& nums) {
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

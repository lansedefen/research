#include<vector>
#include<string>
#include<iostream>
#include"../array/array_head.h"
#include"../array/remove_dumplicate.h"

using namespace std;

int FindMaxKNum(vector<int>& nums, int start, int end, int k) { 
    if (end - start <k) {
        return -1;
    }

    int num = PartVector(nums, start, end);
    if (num - start < k) {
       //cout << "1: num:" << num << ", start:" << num + 1 << ", end:" << end << ", k:" << k + start - num -1 <<endl;
       return FindMaxKNum(nums, num + 1, end, k + start - num -1); 
    }
    else {
       //cout << "2: num:" << num << ", start:" << start << ", end:" << num-1 << ", k:" << k <<endl;
       return FindMaxKNum(nums, start, num-1, k);
    }
}

int FindKMaxNum2(vector<int>& nums_first, int first_index, vector<int>& nums_second, int second_index, int k) {
	cout << "first:" << first_index << ", second_index:"<<second_index << ", k:"<< k << endl;
	if (k == 0) {
		return min(nums_first[first_index], nums_second[second_index]);
	} 
	if ((nums_first.size() - first_index == 1) && nums_second.size()-1 >= k) {
		return nums_second[k];
	}
	if ((nums_second.size() - second_index == 1) && nums_first.size()-1 >= k) {
		return nums_first[k];
	}
	if (nums_first.size() - first_index + nums_second.size() - second_index == k - 1) {
		return max(nums_first[first_index], nums_second[second_index]);
	}

	int idx1 = (k -1)/2;
	int idx2 = (k-1) - idx1;
	cout << "idx1:" << idx1 << ", idx2:" << idx2 << endl;
	if (nums_first[first_index + idx1] == nums_second[second_index + idx2]) {
		return nums_first[first_index + idx1];	
	}
	else if(nums_first[first_index + idx1] < nums_second[second_index + idx2]) {
		return FindKMaxNum2(nums_first, first_index + idx1 + 1, nums_second, second_index, k - idx1 -1);
	} else {
		return FindKMaxNum2(nums_first, first_index, nums_second, second_index + idx2 + 1, k - idx2 -1);
	}
}

int FindMedia(vector<int>& nums_first, vector<int>& nums_second) {
	int m = nums_first.size();
	int n = nums_second.size();
	cout << "m:" << m << ", n:" << n << endl;
	if ((m + n) %2 == 0) {
		return (FindKMaxNum2(nums_first, 0, nums_second, 0, (m + n - 1)/2) + FindKMaxNum2(nums_first, 0, nums_second, 0, (m + n)/2)  ) /2.0 ; 
	} else {
		return FindKMaxNum2(nums_first, 0, nums_second, 0, (m + n)/2); 
	}
	return -1;
}

int main() {
	int first[] = {-1, 0, 2, 4};
    vector<int> nums_first(first, first + 4);
	int second[] = {11, 3, 0, 5, 6};
    vector<int> nums_second(second, second + 5);
 
    int start = 0, end = 4;
    int k = 3;
    FindMaxKNum(nums_second, start , end, k);
    PrintVector(nums_second);

	//int res = FindMedia(nums_first, nums_second);
	//cout << res << endl;
    return -1;
}

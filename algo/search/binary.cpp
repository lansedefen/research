#include<iostream>
#include<vector>

using namespace std;

bool BinarySearch(vector<int>& arr, int start, int end, int val) {
     int mid = (start + end) /2; 
     cout << "start, end, mid:" << start << "," << end << "," << mid << endl;
     while (start < end) {
	     if (arr[mid] == val) {
		     return true;
	     } else if(arr[mid] > val) {
		     end = mid;
	     } else {
	             start = mid + 1;
	     }
	     mid = (start + end) /2;
         cout << "start, end, mid:" << start << "," << end << "," << mid << endl;
     }
     return false;
}

bool SearchRotate(vector<int>& nums, int start, int end, int val) {
	while (start < end) {
		int middle = start + (end - start) /2 ;
		if (nums[middle] == val) {
			return true;
		}

		if (nums[middle] < nums[start]) {
			if(val > nums[middle] && val <= nums[end-1]) {
				start = middle + 1;
			}else {
				end = middle;
			}
		} else {
			if (val >= nums[start] && val < nums[middle] ) {
				end = middle;
			} else {
				start = middle + 1;
			} 	
		}
	}
	return false;
}

bool SearchDupRotate(vector<int>& nums, int start, int end, int val) {
	while (start < end) {
		int middle = start + (end - start) /2 ;
		if (nums[middle] == val) {
			return true;
		}

		if (nums[middle] < nums[start]) {
			if(val > nums[middle] && val <= nums[end-1]) {
				start = middle + 1;
			}else {
				end = middle;
			}
		} else if  (nums[middle] > nums[start]) {
			if (val >= nums[start] && val < nums[middle] ) {
				end = middle;
			} else {
				start = middle + 1;
			} 	
		} else {
			start ++;
		}
	}
	return false;
}

int main() {
   int input[] = {1,2,3,4,5,0};
   vector<int > nums(input, input + 6);

   //bool res = BinarySearch(nums, 0, nums.size(), -1);
   bool res = SearchRotate(nums, 0, nums.size(), 0);

   cout << res  << endl;
}

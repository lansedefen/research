#include<iostream>
#include<vector>
#include"../array/array_head.h"

using namespace std;

int CombineCount(vector<int>& arr, int start, int middle, int end) {
      vector<int> tmp(arr.begin(), arr.end());
      PrintVector(tmp, "tmp");

      int i = start, j = middle;
      int index = start;
    int nums = 0;
      while( i < middle && j < end) {
		  cout << "i:" << i << ", j:" << j << ", tmp_i:" << tmp[i] <<", tmp_j:"<< tmp[j] << ", middle:" << middle << ", end:" << end << endl;
          if (tmp[i] <= tmp[j]) {
	        arr[index++] = tmp[i++];
	      } 

          else {
            nums += (middle - i + 1);
	        arr[index++] = tmp[j++];
	      }
      }

    while(i < middle) {
	    arr[index++] = tmp[i++];
    }

    while(j < end) {
	    arr[index++] = tmp[j++];
    }
	  PrintVector(arr, "arr1");
    return nums;
}

int MergeSort(vector<int>& arr, int start, int end) {
     if (start >= end -1) {
        return 0;
     }
     int middle = start + (end - start) /2;
     int left_nums = MergeSort(arr, start, middle);
     int right_nums = MergeSort(arr, middle, end);
     int middle_nums = CombineCount(arr, start, middle, end);
     return left_nums + right_nums + middle_nums;
}

int main() {
    //int nums[] = {-1, 10, -1, 6, 5, 0};
	//vector<int> arr(nums, nums + 6);

    vector<int> arr;
	CreateVector(arr);
    arr.push_back(-5);
    PrintVector(arr, "arr");
    int res = MergeSort(arr, 0, arr.size());
    PrintVector(arr, "arr" );
    cout << res << endl;
}

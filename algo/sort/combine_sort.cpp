#include<iostream>
#include<vector>
#include"array_head.h"

using namespace std;

void CombineVector(vector<int>& arr, int start, int middle, int end) {
      vector<int> tmp(arr.begin(), arr.end());
      PrintVector(tmp, "tmp");

      int i = start, j = middle + 1;
      int index = start;
      while( i <= middle || j <= end) {
		  cout << "i:" << i << ", j:" << j << ", tmp_i:" << tmp[i] <<", tmp_j:"<< tmp[j] << ", middle:" << middle << ", end:" << end << endl;
          if(j > end || (tmp[i] < tmp[j] && i <= middle)) {
	        arr[index++] = tmp[i++];
            continue;
	      } 

          if (i > middle || (tmp[i] >= tmp[j] && j <= end))  {
	        arr[index++] = tmp[j++];
            continue;
	      }
      }
	  PrintVector(arr, "arr1");
}

void MergeSort(vector<int>& arr, int start, int end) {
     if (start >= end) {
        return;
     }
     int middle = start + (end - start) /2;
     MergeSort(arr, start, middle);
     MergeSort(arr, middle + 1, end);
     CombineVector(arr, start, middle, end);
}

int main() {
    //int nums[] = {-1, 10, -1, 6, 5, 0};
	//vector<int> arr(nums, nums + 6);

    vector<int> arr;
	CreateVector(arr);
    PrintVector(arr, "arr");
    MergeSort(arr, 0, arr.size()-1);
    PrintVector(arr, "arr" );
}

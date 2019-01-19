#include<iostream>
#include<vector>
#include"../array/array_head.h"
#include"../array/merge_array.h"

using namespace std;

void MergeSort(vector<int>& arr, int start, int end) {
     if (start >= end -1) {
        return;
     }

     int middle = start + (end - start) /2;
     cout << "start:" << start << ", middle:" << middle << ", end:" << end << endl;
     MergeSort(arr, start, middle);
     MergeSort(arr, middle, end);
     MergeVector(arr, start, middle, end);
}

int main() {
    //int nums[] = {-1, 10, -1, 6, 5, 0};
	//vector<int> arr(nums, nums + 6);

    vector<int> arr;
	CreateVector(arr);
    PrintVector(arr, "arr");
    MergeSort(arr, 0, arr.size());
    PrintVector(arr, "arr");
}

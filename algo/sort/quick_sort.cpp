#include<iostream>
#include<vector>
#include"array_head.h"

using namespace std;

int PartVector(vector<int>& arr, int start, int end) {
	int i = start, j = end;
	int base = arr[start];
    cout << "start:" << start << ", end:" << end << ", base:" << base << endl;
    PrintVector(arr, "arr1");
	while(i < j) {
	    while (arr[j] >= base && i < j) {
	        j--;
	    }
	    arr[i] = arr[j];

        while (arr[i] <= base && i < j) {
	        i++;
	    }
	    arr[j] = arr[i];
	}
	arr[start] = base;

    PrintVector(arr, "arr2");
    return i;
}

void QuickSort(vector<int>& arr, int start, int end) {
	if(start >= end) {
	   return;
	}

    int middle = PartVector(arr, start, end);
	QuickSort(arr, start, middle - 1);
	QuickSort(arr, middle + 1, end);
}

int main() {
    int tmp[] = {2, 2, -1, 10, 0, 3};
    vector<int > arr(tmp, tmp + 6);
    PrintVector(arr);

    QuickSort(arr, 0, arr.size() - 1);
    PrintVector(arr);
    return -1;
}

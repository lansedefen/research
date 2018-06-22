#include<iostream>
#include<vector>

using namespace std;

void quick_sort(vector<int>& arr, int left, int right) {
	if(left >= right) {
	   return;
	}
	int i, j = right;
        i = left;
	int base = arr[left];
	while(left < right) {
	    while (arr[right] >= base && left < right) {
	        right--;
	    }
	    arr[left] = arr[right];
            while (arr[left] <= base && left < right) {
	        left++;
	    }
	    arr[right] = arr[left];
	}
	arr[left] = base;
	quick_sort(arr, i, left - 1);
	quick_sort(arr, left + 1, j);
}

int main() {
    int tmp[6] = {2, 2, -1, 10, 0, 3};
    vector<int > arr(begin(tmp), end(tmp));
    for (int i=0; i < arr.size(); i++) {
       cout << arr[i] << endl;
    }
    cout << "----------------" << endl;;
    quick_sort(arr, 0, arr.size() - 1);
    for (int i=0; i < arr.size(); i++) {
       cout << arr[i] << endl;
    }
}

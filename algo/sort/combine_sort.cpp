#include<iostream>
#include<vector>

using namespace std;

void combine(vector<int>& arr, int start, int mid, int end) {
      vector<int> left;
      vector<int> right;
      cout << "*****" << endl;
      for(int i =0;i< arr.size();i++) {
        cout << arr[i] << endl;
      }
      cout << "****" << endl;
      for(int i= start; i<=mid; i++) {
         left.push_back(arr[i]);
	 cout << "left" << arr[i] << endl;
      }
      for(int j = mid+1; j<=end; j++) {
         right.push_back(arr[j]);
	 cout << "right" << arr[j] << endl;
      }
      int i = 0;
      int j = mid + 1;
      int index = start;
      cout << "combine--start:" << start <<", mid:" << mid << ", end:" << end << endl; 
      while( i <= mid || j <= end) {
          if(i > mid) {
	      arr[index] = right[j-mid-1];
	      j++;
              index ++;
	      continue;
	  }

	  if(j > end) {
	      arr[index] = left[i];
	      i++;
	      index++;
	      continue;
	  }
          if(left[i] < right[j -mid -1]) {
	      arr[index] = left[i];
	      i++;
	  }
          else {
	      arr[index] = right[j -mid -1];
	      j++;
	  }
          index ++;
      }
      cout << "++++++" << endl;
      for(int i =0;i< arr.size();i++) {
        cout << arr[i] << endl;
      }
      cout << "+++++++" << endl;
}

void merge_sort(vector<int>& arr, int start, int end) {
     if (start < end) {
         int mid = (start + end) /2;
         cout << "start:" << start << ",mid:" << mid << ",end:" << end << endl;;
         merge_sort(arr, start, mid);
         merge_sort(arr, mid+1, end);
         combine(arr, start, mid, end);
     }
}

int main() {
    vector<int> arr;
    arr.push_back(-1);
    arr.push_back(10);
    arr.push_back(3);
    arr.push_back(2);
    for (int i = 0;i < arr.size();i++) {
       cout << arr[i] << endl;
    }
    int end = arr.size() -1;
    merge_sort(arr, 0, end);
    cout << "------------" << endl;
    for (int i = 0;i < arr.size();i++) {
       cout << arr[i] << endl;
    }
}

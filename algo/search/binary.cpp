#include<iostream>
#include<vector>

using namespace std;

bool bin_search(vector<int>& arr, int start, int end, int val) {
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

int main() {
   vector<int > arr;
   arr.push_back(1);
   arr.push_back(4);

   /*
   arr.push_back(6);
   arr.push_back(9);
   arr.push_back(9);
   arr.push_back(9);
   */
   bool x = bin_search(arr,0,arr.size(), -1);
   cout << x << endl;
}

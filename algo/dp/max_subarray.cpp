#include<vector>
#include<iostream>

using namespace std;

void MaxSumSubArray(vector<int>& array) {
    vector<int> dp(array.size(), 0);
	dp[0] = array[0];
	for(int i = 1 ; i<array.size();i++) {
			//if (array[i] >= 0) {
		        dp[i]  = dp[i-1] + array[i] ;
			//}
	}
    for(int i =0; i< dp.size(); i++) {
	     cout << dp[i] << endl;
	}
}

void MaxMutiplySubArray(vector<int>& array) {
	vector<int> dp_max(array.size(), 0);
	vector<int> dp_min(array.size(), 0);
	dp_max[0] = dp_min[0] = array[0];
	for(int i=1; i < array.size();i++) {
	     dp_max[i] = max( dp_max[i-1] * array[i], dp_min[i-1] * array[i] );
		 dp_max[i] = max( dp_max[i], array[i]); 
	     dp_min[i] = min( dp_max[i-1] * array[i], dp_min[i-1] * array[i] );
		 dp_min[i] = min( dp_min[i], array[i]); 
	}
    for(int i =0; i< dp_max.size(); i++) {
	     cout << dp_max[i] << endl;
	}
}

int main() {
   int tmp[] = {1, -2, 3, -4, 0, 5};
   vector<int> array(tmp, tmp + 6);
   cout << tmp << endl;
   //MaxSumSubArray(array);
   MaxMutiplySubArray(array);
}

#include<vector>
#include<string>
#include<iostream>

using namespace std;

int MaxCycleString(string target) {
	vector<int> tmp(target.size(), 0);
    vector<vector<int> > dp(target.size(), tmp);

    for (int i=0; i < dp.size(); i++) {
	   for(int j =0; j< dp[i].size();j++) {
	      if ( j-i == 1) {
				  if(target[i] == target[j]) {
				       dp[i][j] =2;
				  } else {
				       dp[i][j] =0;
				  }
		  }
		  if (i==j) {
		     dp[i][j] =1;
		  }
	      cout << dp[i][j] << ",";
	   }
	   cout << endl;
	}

	for(float i= 0; i< target.size(); i++) {
	   for(int dis = 1; dis < target.size(); dis++){
			for(int k=0; k <2; k++) {
					int left = i - dis + k;
					int right = i + dis;
					if( 0 <=left && right < target.size() ) {
							cout << left << "," << right << " " << target[left] << "," << target[right] << " ";
							if(target[left] == target[right]) {
								 dp[left][right] = dp[left+1][right-1] + 2;
							} else {
								 int tmp_value = max(dp[left+1][right-1], dp[left+1][right]); 
								 dp[left][right] = max(tmp_value, dp[left][right-1]);		
							}
					 }
			}
	   }
	   cout << endl;
	}

	cout << "----------" << endl;
    for (int i=0; i < dp.size(); i++) {
	   for(int j =0; j< dp[i].size();j++) {
	      cout << dp[i][j] << ",";
	   }
	   cout << endl;
	}
	return -1;
}

int main() {
   string target = "cxbbacd";
   cout << "target:" << target << endl;
   MaxCycleString(target);
   return -1; 
}

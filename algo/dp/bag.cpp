#include<iostream>
#include <algorithm>
#include <iterator> 
#include<vector>

using namespace std;

void Solve01Bag() {
     int num = 4;
     int max_weight = 15;

     int tmp_w[] ={0,1,3,5,7}; // 重量
     int tmp_val[] ={0,10,3,1,2}; // 价值
     vector<int> w(tmp_w , tmp_w + 5);
     vector<int> val(tmp_val, tmp_val + 5);

     vector<int> first(max_weight, 0);
     // i: 1-num 
     // j: 背包重量 0 - max_weight
     for(int i = 1; i <= num; i++) { // 物品
         for(int j = max_weight; j >= 0; j--) { //
             if (j >= w[i]) {
		 		first[j] = max(first[j], first[j-w[i]] + val[i]); 
             } 
         }
     }
     cout << "----------------" << endl;
	 typedef ostream_iterator<int> ostream_iter;
	 copy(first.begin(), first.end(), ostream_iter(cout, " "));
}

int main() {
	Solve01Bag();
	return -1;
}


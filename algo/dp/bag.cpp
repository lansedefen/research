#include<iostream>
#include <algorithm>
#include <iterator> 
#include<vector>

using namespace std;

void Solve01Bag(int max_weight, vector<int>& weight, vector<int>& value) {
     int num = weight.size() -1;
     vector<int> first(max_weight, 0);
     // i: 1-num 
     // j: 背包重量 0 - max_weight
     for(int i = 1; i <= num; i++) { // 物品
         for(int j = max_weight; j >= 0; j--) { //
             if (j >= weight[i]) {
		 		first[j] = max(first[j], first[j-weight[i]] + value[i]); 
             } 
         }
     }
     cout << "----------------" << endl;
	 typedef ostream_iterator<int> ostream_iter;
	 copy(first.begin(), first.end(), ostream_iter(cout, " "));
}

void SolveManyBag(int max_weight, vector<int>& weight, vector<int>& value, vector<int>& goods_num) {
		vector<int> divide_weight;
		vector<int> divide_value;
		for(int i = 1; i<= weight.size(); i++) {
				int num = goods_num[i];
				for(int j = 1; j <= num;  j = j<<1) {
					divide_weight.push_back(j * weight[i] );
					divide_value.push_back( j * value[i] );
					num -= j;
				}
				if( num > 0) {
					divide_weight.push_back(num * weight[i]);
					divide_value.push_back( num * value[i]);
				}
		}
		for(int i = 0; i< divide_value.size();i++) {
		   cout << divide_value[i] << " " << divide_weight[i] << endl;
		}
}

int main() {
    int tmp_w[] ={0,1,3,5,7}; // 重量
    int tmp_val[] ={0,4,3,1,2}; // 价值
    vector<int> w(tmp_w , tmp_w + 5);
    vector<int> val(tmp_val, tmp_val + 5);
	int max_weight = 15;
	
	int num[] = {0,3,4,5,1};
	vector<int> goods_num(num, num + 5);
	//Solve01Bag(max_weight, w, val);
    SolveManyBag(max_weight, w, val, goods_num);
	return -1;
}


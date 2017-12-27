#include<iostream>
#include <algorithm>
#include <iterator> 
#include<vector>

using namespace std;

int main() {
     int num = 4;
     int max_weight = 15;

     int tmp_w[] ={0,1,3,5,7}; // 重量
     int tmp_val[] ={0,10,3,1,2}; // 价值
     vector<int> w(tmp_w , tmp_w + 5);
     vector<int> val(tmp_val, tmp_val + 5);
     
     vector<vector<int> > array(num + 1, vector<int>(max_weight, 0)); 
     for (int i = 0; i < array.size(); i++) { 
         for (int j = 0; j < array[i].size();j++)
         {
             cout << array[i][j] << ",";
         }
         cout << endl;
     }

     // array[i][j] 前i个物品，重量为j时，最大价值
     // i: 1-num 
     // j: 背包重量 0 - max_weight
     for(int i = 1; i <= num; i++) { // 物品
         for(int j = 0; j <= max_weight; j++) { //
             if (j >= w[i]) {
                 array[i][j] = max(array[i-1][j], array[i-1][j - w[i]] + val[i]);
             } 
             else {
                 array[i][j] = array[i-1][j];
             }
         }
     }

     cout << "----------------" << endl;
     for (int i = 0; i < array.size(); i++) { 
         for (int j = 0; j < array[i].size();j++)
         {
             cout << array[i][j] << ",";
         }
         cout << endl;
     }
     return -1;
}


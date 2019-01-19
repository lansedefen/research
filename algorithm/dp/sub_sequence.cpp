#include<iostream>
#include<vector>
#include<string>

using namespace std;

void GetMaxSubSequence(vector<int>& input_array, vector<int>& output_array) {
    //dp[i] 以第i个字符结尾，最大递增序列长度
    //if a[i] > a[j], dp[i] = dp[j] + 1
    //else dp[i] = 1
    // dp[0-len] = 1
    vector<int> dp(input_array.size(), 1);
    for(int i=0; i< input_array.size(); i++) {
       for(int j=0; j< i; j++) {
           if(input_array[i] > input_array[j]) {
               dp[i] = max(dp[i], dp[j] + 1);
           }
       }
    }
    for(int i =0; i<dp.size(); i++) {
       cout << dp[i] << ",";
    }
    cout << endl;
}

int main() {
    int tmp[] = {1,3,0,4,2,9,8,7};
    vector<int> input_array(tmp, tmp + 8);
    for(int i =0; i<input_array.size(); i++) {
        cout << input_array[i] << ",";
    }
    cout << endl;
    vector<int> output_array;
    GetMaxSubSequence(input_array, output_array);
}

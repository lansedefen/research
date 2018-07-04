#include<iostream>
#include<vector>
#include<string>

using namespace std;

void PrintVector(vector<int>& nums, string name = "") {
     if (name != "") {
        cout << name << ":\t";
     }
     
     for (int i = 0; i < nums.size(); i++) {
        cout << nums[i] << ", ";
     }
     cout << endl;
}

#include<vector>
#include<string>
#include<iostream>

using namespace std;


int AdjustVector(vector<int>& input, int start, int end); 

bool FindMaxKNum(vector<int>& input, int start, int end, int k) { 
    int num = AdjustVector(input, start, end);
    cout << "num:" << num << ", start:" << start << ", end:" << end << ", k:" << k <<endl;
    if (num - start == k) {
        return true; 
    }
    else if (num - start < k) {
       cout << "1: num:" << num << ", start:" << num + 1 << ", end:" << end << ", k:" << k + start - num -1 <<endl;
       return FindMaxKNum(input, num + 1, end, k + start - num -1); 
    }
    else {
       cout << "2: num:" << num << ", start:" << start << ", end:" << num-1 << ", k:" << k <<endl;
       return FindMaxKNum(input, start, num-1, k);
    }
}

int AdjustVector(vector<int>& input, int start, int end) {
    for(int i=0;i< input.size(); i++) {
        cout << input[i] << ",";    
    }
    cout << endl;
    int base = input[start];
    int i = start;
    int j = end;
    while (i < j) {
        while (i < j && input[j] > base) {
            j--;
        }
        cout << "j:" << j << ", i:"<< i <<endl;
        if (i<=j) {
            input[i] = input[j];
        }

        for(int k=0; k< input.size(); k++) {
            cout << input[k] << ",";    
        }
        cout << endl;

        while (i<j && input[i] <= base) {
            i++;
        }
        cout << "i:" << i << ", j:"<< j << endl;
        if (i<=j) {
            input[j] = input[i];
        }

        for(int k=0; k< input.size(); k++) {
            cout << input[k] << ",";    
        }
        cout << endl;
    }

    input[i] = base;

    cout << "-----------------" << endl;
    for(int i=0;i< input.size(); i++) {
        cout << input[i] << ",";    
    }
    cout << endl;
    return i;
}

int main() {
    vector<int> input;
    input.push_back(1);
    input.push_back(-1);
    input.push_back(2);
    input.push_back(0);
    input.push_back(6);
    input.push_back(5);
    input.push_back(1);
    int start = 0;
    int end = 6;
    // AdjustVector(input, start , end);
    int k = 4;
    cout << "k:" << k << endl;
    FindMaxKNum(input, start , end, k);
    return -1;
}

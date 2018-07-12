#include<iostream>
#include<vector>
#include<string>
#include"../array/array_head.h"

using namespace std;

void pailie(vector<int>& input, vector<int>& label, vector<int>& res, int index) {
    if( res.size() == index) {
        PrintVector(res);
    }

    for(int i= 0; i < input.size(); i++){
        if (label[i] == 0) {
            res.push_back(input[i]);
            label[i] = 1;
            pailie(input, label, res, index);
            res.pop_back();
            label[i] = 0;
        }
    }
}

void zuhe(vector<int>& input, int cur, vector<int>& res, int index) {
    if (res.size() == index) {
        PrintVector(res);
    }

    for (int i = cur; i< input.size(); i++) {
            res.push_back(input[i]);
            zuhe(input, cur+1, res, index);
            res.pop_back();
    }
}

void FindPath(vector<vector<int> >& matrix, vector<vector<int> >& label, vector<int>& res, string target, int i,int j) {
    if ( label[i][j]== 0 && 
         (i+1 >= label.size() || (i+1 < label.size() && label[i+1][j]== 0)) && 
         (j+1 >= label.size() || (j+1 < label[0].size() && label[i][j+1]== 0)) && 
         (j-1 <=0 || (j-1 >=0 && label[i][j-1]== 0)) && 
         (i-1 <=0 || (i-1 >=0 && label[i-1][j] == 0 )) ) {
        for(int k=0;k < res.size(); k++) {
            cout << res[k] << ","; 
        }
        cout << endl;
    }

    if (j+1 < label[i].size() && label[i][j+1] == 1) {
        label[i][j+1] = 0;
        res.push_back(matrix[i][j+1]);
        FindPath(matrix, label, res, target, i, j+1);
        label[i][j+1] = 1;
        res.pop_back();
    }

    if (i+1 < label.size() && label[i+1][j] == 1) {
        label[i+1][j] = 0;
        res.push_back(matrix[i+1][j]);
        FindPath(matrix, label, res, target, i+1, j);
        label[i+1][j] = 1;
        res.pop_back();
    }

    if (i-1>= 0 && label[i-1][j] == 1) {
        label[i-1][j] = 0;
        res.push_back(matrix[i-1][j]);
        FindPath(matrix, label, res, target, i-1, j);
        label[i-1][j] = 1;
        res.pop_back();
    }

    if (j-1>=0 && label[i][j-1] == 1) {
         label[i][j-1] = 0;
         res.push_back(matrix[i][j-1]);
         FindPath(matrix, label, res , target, i, j-1);
         label[i][j-1] = 1;
         res.pop_back();
    }
}

int main() {
    int nums[] = {1,2,3,4,5};
    vector<int> input(nums, nums+5);
    vector<int> res;
    int index = 5;
    //pailie(input, label, res, index);
    zuhe(input, 0, res, 3);

    /*
    vector<vector<int> > matrix(4, vector<int>(4, 0));
    matrix[0][1] = 1;
    matrix[0][2] = 2;
    matrix[0][3] = 3;
    matrix[1][0] = 4;
    matrix[1][1] = 5;
    matrix[1][2] = 6;
    matrix[1][3] = 7;
    matrix[2][0] = 8;
    matrix[2][1] = 9;

    label[0][0] = 0;
    res.push_back(0);
    FindPath(matrix, label, res, "abc", 0, 0);
    //Get3Sum(input, label, res, index);
    */
    return -1;
}

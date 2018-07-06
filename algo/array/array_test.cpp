#include<iostream>
#include<vector>
#include"array_head.h"
//#include "remove_dumplicate.h"
#include "merge_array.h"
//#include "ksum.h"

using namespace std;

int main() {
    // 1
    /*
	int num_array[] = {1,1,1,2,3,3,4,4};
	vector<int> nums(num_array, num_array + 8);
	RemoveDuplicates(nums);
	RemoveKDuplicates(nums);
    RemoveNum(nums, 3); 

    PrintVector(nums);
    PartVector(nums); 
    PrintVector(nums);
    //MoveArray(nums);
    */

    //2
	//int tmp[] = {1, 2, 3, 3, 4, 5};
	//vector<int> array_input(tmp, tmp+6);
	//Get2sum(array_input, 7);
	//Get3sum(array_input, 7);
	//Get4sum(array_input, 7);

    //3
    int a[] = {1,2,3, 6};
    vector<int> v_a(a, a+4);
    int b[] = {2,2,5};
    vector<int> v_b(b, b+3);
    PrintVector(v_a, "v_a");
    PrintVector(v_b, "v_b");
    Merge2Vector(v_a, v_b);
    PrintVector(v_a);

    vector<vector<int> > arrays;
    arrays.push_back(v_a);
    arrays.push_back(v_b);
    vector<int> output;
    //MergeKVector(arrays, output);
    // 4
    return -1;
}	

#include<iostream>
#include<vector>
#include<stdlib.h>
#include"../array/array_head.h"

using namespace std;

int adjust(vector<int>& loster_tree, vector<int>& leaves, int i) {
     int K = leaves.size();
     int parent = (K -2 + i) /2;
     
     while (parent >0) {
	    if( leaves[i] > leaves[loster_tree[parent]] ) {
            swap(loster_tree[parent], i);
	     }
         parent = parent /2;
     } 
     loster_tree[K-1] = i;
     return -1;
}

void build(vector<int>& loster_tree, vector<int>& leaves) {
    int K = leaves.size();
    loster_tree.resize(K);
    for (int i= K-1; i>=0; i--) {
	    adjust(loster_tree, leaves, i);
    } 
}

int main() {
    int nums[] = {3,6,1,8,9};
    vector<int> leaves(nums, nums + 5);
    vector<int> loster_tree;
    build(loster_tree, leaves);
    PrintVector(leaves);
    PrintVector(loster_tree);
    return -1;
}

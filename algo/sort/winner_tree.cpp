#include<vector>
#include<iostream>
#include"../array/array_head.h"

using namespace std;

void AdjustTree(vector<int>& tree, vector<int>& leaves, int i) {  
	int K = leaves.size();
	int m, n;
	int left_index = 2*i + 1;
	if( left_index < K - 1)               /* 获取它的左孩子结点 */  
		m = tree[left_index];  
	else  
		m = left_index - (K - 1);  
 
	int right_index = 2*i + 2;
	if(right_index < K -1)                 /* 获取它的右孩子节点 */  
		n = tree[right_index];  
	else  
		n = right_index - (K - 1);  
	tree[i] = leaves[m] > leaves[n] ? m : n; /* 进行胜负判定 */  
}  

void BuildTree(vector<int>& tree, vector<int>& leaves)  {  
	tree.resize(leaves.size() - 1);
	for(int i = tree.size()-1; i>=0; i--)  
        AdjustTree(tree, leaves, i);  
}  

void DeleteTree(vector<int>& tree, vector<int>& leaves, int& value)  {  
	value = leaves[tree[0]];
	swap(leaves.back(), leaves[tree[0]]);
	leaves.pop_back();
	BuildTree(tree, leaves); 
}

int main()  {  
    int nums[] = {3, 6, 1, 8, 9};
    vector<int> leaves(nums, nums + 5);
    vector<int> tree;

    PrintVector(leaves, "leaves");    
    BuildTree(tree, leaves); 
    PrintVector(tree, "tree");    

    return 0;  
}  

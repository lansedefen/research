#include<vector>
#include<iostream>
#include"../array/array_head.h"

using namespace std;

void AdjustTree(vector<int>& tree, vector<int>& leaves, int i) {  
 int K = leaves.size();
 int m, n;  
 if(2 * i < K)               /* 获取它的左孩子结点 */  
     m = tree[2 * i + 1];  
 else  
     m = 2 * i - K + 1;  

 if(2 * i + 1 < K)                 /* 获取它的右孩子节点 */  
     n = tree[2*i + 2];  
 else  
     n = 2 * i + - K + 2;  

 tree[i] = leaves[m] > leaves[n] ? n : m; /* 进行胜负判定 */  
}  

void BuildTree(vector<int>& tree, vector<int>& leaves)  {  
 tree.clear();
 for(int i = tree.size()-1; i>=0; i--)  
     AdjustTree(tree, leaves, i);  
}  

int main()  {  
    int nums[] = {3, 6, 1, 8, 9};
    vector<int> leaves(nums, nums + 5);
    vector<int> tree(0, 5);
    BuildTree(leaves, tree); 
    PrintVector(leaves, "before");    
    return 0;  
}  

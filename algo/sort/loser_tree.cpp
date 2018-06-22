#include<iostream>
#include<vector>
#include<stdlib.h>

using namespace std;

void adjust(vector<int>& loster_tree, vector<int>& leaves, int i, int K) {
     int parent = (K + i) /2;
     while (parent >0) {
	 if( leaves[i] > leaves[loster_tree[parent]] ) {
             int tmp = loster_tree[parent];
	     loster_tree[parent] = i;
	     i = tmp;
	 }
         parent = parent /2;
     } 
     loster_tree[0] = i; 
}

void build(vector<int>& loster_tree, vector<int>& leaves, int K) {
    for (int i= K-1; i>=0; i--) {
	    adjust(loster_tree, leaves, i, K);
    } 
}

int main() {
    int K = 5;
    const int MINKEY = -1000;
    vector<int> loster_tree(K);
    vector<int> leaves(K+1);
    cout << "K:" <<  K << endl;
    // leaves, 0~K-1 存放K路排序数，K存放初始化最小值
    // loster_tree, 1~K-1 存放失败者，0 存放冠军
    leaves[K] = MINKEY;
    for (int i = 0;i < K; i++) {
        leaves[i] = rand() % 10 ;
	cout << "init leaves:" << i << " value:"<< leaves[i] << endl;
	loster_tree[i] = K;
    }
    // 
    build(loster_tree, leaves, K);
    for (int i = 0;i < K; i++) {
	cout << "build loster_trees:" << i << " value:"<< loster_tree[i] << endl;
    }
}

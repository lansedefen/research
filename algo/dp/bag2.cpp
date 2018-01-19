#include<iostream>
#include <algorithm>
#include <iterator> 
#include<vector>

using namespace std;

void Solve01Bag() {
     int num = 4;
     int max_weight = 15;

     int tmp_w[] ={0,1,3,5,7}; // 重量
     int tmp_val[] ={0,10,3,1,2}; // 价值
     vector<int> w(tmp_w , tmp_w + 5);
     vector<int> val(tmp_val, tmp_val + 5);

     vector<int> first(max_weight, 0);
     // i: 1-num 
     // j: 背包重量 0 - max_weight
     for(int i = 1; i <= num; i++) { // 物品
         for(int j = max_weight; j >= 0; j--) { //
             if (j >= w[i]) {
		 		first[j] = max(first[j], first[j-w[i]] + val[i]); 
             } 
         }
     }
     cout << "----------------" << endl;
	 typedef ostream_iterator<int> ostream_iter;
	 copy(first.begin(), first.end(), ostream_iter(cout, " "));
}

void SolveFullBag() {
     int num = 4;
     int max_weight = 15;
     int tmp_w[] ={0,3,4,5,2}; // 重量
     int tmp_val[] ={0,10,3,1,2}; // 价值
     vector<int> weight(tmp_w , tmp_w + 5);
     vector<int> value(tmp_val, tmp_val + 5);

     vector<int> first(max_weight, 0);
     for(int j= 0; j<= max_weight; j++) {
         for(int i = 1; i<= num; i++) {
            if(j >= weight[i]) {
                first[j] = max(first[j], first[j-weight[i]] + value[i]);
            }
         }
     }
     copy(first.begin(),first.end(), ostream_iterator<int>(cout, " "));
}

void SolveManyBag() {    


}
 
/* 多重背包 二进制拆分
 * Time Complexity  大于O(N*V)
 * Space Complexity O(N*V)
 * 设 V <= 200 N <= 10 ，拆分后 物品总数 < 50
 * 每件物品有 log n[i]种状态
 */
int maxV[201];
int weight[50]; /* 记录拆分后物体重量 */
int value[50];  /* 记录拆分后物体价值 */
int V, N;
void test() {
    int i, j;
    V = 4;
    N = 10;
    int weig, val, num;
    int count = 0;
    for(i = 0; i < N; ++i)
    {
        //scanf("%d %d %d",&weig,&val,&num);
        weig = 4, val =3, num =3;
        for(j = 1; j <= num; j <= 1) // 二进制拆分
        {
            weight[count] = j * weig;
            value[count++] = j * val;
            num -= j;
        }

        if(num > 0) {
            weight[count] = num * weig;
            value[count++] = num * val;
        }
    }

    for(i = 0; i < count; ++i) {
        for(j = V; j >= weight[i]; --j)
        {
            int tmp = maxV[j-weight[i]] + value[i];
            maxV[j] = maxV[j] > tmp ? maxV[j] : tmp;
        }
    }

    cout << maxV[V] << endl;;
    //printf("%d",maxV[V]);
}

int main() {
    //Solve01Bag();
	//SolveFullBag();
    test();
	return -1;
}


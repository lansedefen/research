#ifndef MERGE_ARRAY_H_                                                
#define MERGE_ARRAY_H_ 

#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
#include"array_head.h"

using namespace std;

struct cmp {
    bool operator() (pair<int, int> a, pair<int, int> b) {
        return a.first > b.first;
    }
};

/*
int MergeKVector(vector<vector<int> >& arrays, vector<int>& output) {
    priority_queue<pair<int, int>, vector<pair<int, int> >, cmp > q;

    for(int i=0;i < arrays.size();i++) {
        if (arrays[i].size() !=0) {
            q.push( pair<int, int>(0, i));
        }
    }

    output.clear();
    while(!q.empty()) {
        pair<int, int> res = q.top();
        q.pop();
        output.push_back(res.first);

        if (arrays[res.second].size() > 0) {
            q.push(pair<int, int>(arrays[res.second][0], i) );
        }
    }
    
}
*/

int Merge2Vector(vector<int >&A, vector<int>& B) {
    int m = A.size(), n = B.size();
    cout << "m:" << m << ", n:" << n << endl;
    A.resize(m+n);
    int i = m-1, j = n-1, k = m + n -1;
    while(i>=0 && j >=0) {
        A[k--] = A[i] > B[j] ? A[i--]: B[j--];
    }

    while(i >=0) {
        A[k--] = A[i--];
    }
    while(j >=0) {
        A[k--] = A[j--];
    }
    return -1;
}

int MergeVector(vector<int>& arr, int start, int middle, int end) {
      vector<int> tmp(arr.begin(), arr.end());
      PrintVector(tmp, "tmp");

      int i = start, j = middle + 1;
      int index = start;
      while( i <= middle || j <= end) {
          if(tmp[i] < tmp[j]) {
	        arr[index++] = tmp[i++];
	      } else { 
	        arr[index++] = tmp[j++];
	      }
      }

      while(i <=middle) {
        arr[index++] = tmp[i++];
      }
      while (j <=end) {
        arr[index++] = tmp[j++];
      }
	  PrintVector(arr, "arr1");
     return -1;
}

#endif

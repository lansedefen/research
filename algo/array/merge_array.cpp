#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>

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
    A.resize(m+n);
    int i = m-1, j = n-1, k = m + n -1;

    while(i>=0 || j >=0) {
        A[k--] = A[i] > B[j] ? A[i--]:B[j--];
    }
    return -1;
}

void print(int num) { 
    std::cout <<  num << ", "; 
}

int main() {
    int a[] = {1,2,3};
    vector<int> v_a(a, a+3);
    int b[] = {2,2,5};
    vector<int> v_b(b, b+3);
    vector<vector<int> > arrays;
    arrays.push_back(v_a);
    arrays.push_back(v_b);

    vector<int> output;
    //MergeKVector(arrays, output);
    for_each (output.begin(), output.end(), print);     
    cout << endl;

    Merge2Vector(v_a, v_b);
    for_each (v_a.begin(), v_a.end(), print);     
    cout <<endl;
    return -1;
}

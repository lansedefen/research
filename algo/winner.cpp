#include<vector>
#include<iostream>

using namespace std;

void adjust() {

}

void build(vector<int>& ls, vector<int>& b, int k) {
    for(int i = ls.size() - 1; i>0; i--) {
        cout << i <<":" <<ls[i] << endl;
        int left = (i + k)/2 -1;
        int right = (i + k)/2; 
        cout << "left:" <<left << "right:" << right << endl;
    }
}

int main() {
    int xx;
    int k = 5;
    vector<int> ls(5);
    vector<int> b;
    b.push_back(12);
    b.push_back(2);
    b.push_back(3);
    b.push_back(4);
    b.push_back(5);
    build(ls, b, k); 
}

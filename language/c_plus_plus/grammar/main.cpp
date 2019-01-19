#include<vector>
#include<string>
#include<iostream>

using namespace std;

class tool {
    public:
    tool(int yy): xx(yy) {cout << "tool()" << endl;}
    ~tool() {cout << "~tool()" << endl;}

    int xx;
};


class All {
    public:
    All(tool fi): tmp(fi) {cout<< "ALL()" << endl; }
    ~All() { cout <<"~ALL()" << endl;}

    tool tmp;
};


int main() {
    vector<int> tmp1;
    tmp1.push_back(12);
    tmp1.push_back(11);
    tool tmp(10);
    All xx(tmp);

    return -1;
}

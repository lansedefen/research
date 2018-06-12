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
    tool tmp(10);
    All xx(tmp);

    return -1;
}

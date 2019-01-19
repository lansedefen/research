#include<iostream>
#include<vector>

using namespace std;

double Power(double x, int n) {
	if (n==0) {
		return 1.0;
	}

	double v = Power(x, n/2);
	if (n%2 ==0) {
		return v*v;
	} else {
		return v*v*x;
	}
}

double GetPow(double x, int n) {
	if (n<0) {
		return 1.0 / Power(x, -n);
	} else {
		return Power(x, n);
	}
}

double Sqrt(double x) {


}

int main() {
	double res = GetPow(2,8);
	cout << res << endl;
	return -1;
}

#include<vector>
#include<string>
#include<iostream>

using namespace std;

int Add2BigNum(string one, string two) {
	vector<int> result;
	int max_length = max(one.size(), two.size());
	int last = 0;
	for (int i=0;i < max_length; i++) {
		int first =0; int second = 0;
	
		if( i< one.size()) {
			first = int(one[i]) - 48;
		}		

		if (i < two.size()) {
			second = int(two[i]) - 48;
		}
		int res = first + second + last;
		if (i < one.size() && i < two.size()) {
			cout << one[i] << "," <<two[i] << "," << first << "," << second << "," << last << ","<<res << endl;
		}
		result.push_back(res % 10);
		last = res / 10;
	}	
	if (last != 0) {
		result.push_back(last);
	}
	cout << "----------------" << endl;
	for (int i=0; i< result.size();i++) {
			cout << result[i] << "," ;
	}
	cout << endl;
	return -1;
}

int main() {
	string one = "223129";
	string two = "903123";
	cout << "one: " << one << endl;
	cout << "two: " << two << endl;
	Add2BigNum(one ,two);
}

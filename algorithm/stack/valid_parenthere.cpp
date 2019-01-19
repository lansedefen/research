#include<stack>
#include<string>
#include<iostream>

using namespace std;

int LongValidParenthese(const string& s) {
	stack<int> left;
	int last = -1;
	int max_len = 0;
	for(int i =0; i< s.size();i++) {
		if (s[i] == '(') {
			left.push(i);
		} else {
			if (left.empty()) {
				last = i;
			} else {
				left.pop();
				if (!left.empty()) {
					max_len = max(max_len, i - left.top());
				} else {
					max_len = max(max_len, i- last);
				}
			}
		}
	}
	return max_len;
}

int main() {
	string s = "(()))()()()()";
	int res = LongValidParenthese(s);
	cout << res << endl;
}

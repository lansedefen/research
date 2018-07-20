#include<iostream>
#include<string>
#include<stack>
#include<vector>

using namespace std;

bool IsOpreator(const string& word) {
	return word.size() == 1 && string("+-*/").find(word) != string::npos;
}

int EvalReverseExpree(vector<string>& token) {
	stack<int> s;
	for(int i=0; i < token.size(); i++) {
		if (IsOpreator(token[i]) ) {
				int x = s.top();
				s.pop();
				int y = s.top();
				s.pop();
				if (token[i] == string("+")) { 
					x +=y;
				} else if (token[i] == string("-") ) {
					x -=y;
				} else if (token[i] == string("*") ) {
					x *=y;
				} else {
					x /=y;
				}
				s.push(x);
		  } else {
				int value;
				s.push(stoi(token[i]));			
		  }
		  cout << token[i] << endl;
	}
	return s.top();
}

int main() {
	string tmp[] = {"2", "1", "+", "3", "*"};
	vector<string> tokens(tmp, tmp + 5) ;
	int res = EvalReverseExpree(tokens);
	cout << res << endl;
	return -1;
}

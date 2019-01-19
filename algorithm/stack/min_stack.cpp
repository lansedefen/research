#include<iostream>
#include<vector>
#include<string>
#include<stack>

using namespace std;

class MinStack {
  public:
		stack<int> data;
		stack<int> min_data;
		
		void push(int value) {
			data.push(value);
			if (min_data.empty() || value <= min_data.top()) {
				min_data.push(value);
			}
		}

		void pop() {
			int value = data.top();
			data.pop();
			if ( value == min_data.top() )
				min_data.pop();
		}
		
		int top() {
			return data.top();
		}

		int getmin() {
			return min_data.top();
		}
};

class MinStack2 {
  public:
		stack<int> diff;
		int min_value;

		void push(void value) {
			if(diff.empty()) {
				diff.push(0);
				min_value = value;
			} else {
				int diff_value = value - min_value;
				diff.push(diff_value);
				min_value = diff_value < 0 ? value : min_value;
			}
		}

		void pop() {
			int top = diff.top();
			min_value = 0;
		}
};

int main() {
	MinStack tmp;
	tmp.push(11);
	tmp.push(2);
	tmp.push(3);
	return -1;	
}

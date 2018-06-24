#include<string>
#include<iostream>
#include<vector>
#include <unordered_map>

using namespace std;

int Get2sum(vector<int>& array_input, int target) {
	int i = 0;
	int j = array_input.size() -1;
	while(i<j) {
		int res = array_input[i] + array_input[j];
		if(res == target) {
			cout << array_input[i] << ", " << array_input[j] << endl;
			i++; j--;
		} else if ( res < target) {
			i++;	
		} else {
			j--;
		}
	}
	return -1;
}

int Get3sum(vector<int>& array_input, int target) {
	int j = array_input.size() -1;
	for (int k = 0; k < array_input.size(); k++ ) { 
		int tmp_target = target - array_input[k];
		int i = k + 1;
		while(i<j) {
			int res = array_input[i] + array_input[j];
			if(res == tmp_target) {
				cout << array_input[k] << ", " << array_input[i] << ", " << array_input[j] << endl;
				i++; j--;
			} else if ( res < target) {
				i++;	
			} else {
				j--;
			}
		}
	}
	return -1;
}

int Get4sum(vector<int>& array_input, int target) {
	vector<int> sum_input;
	for(int i = 0;i < array_input.size();i++) {
		for(int j = i+1; j < array_input.size();j++) {
				sum_input.push_back(array_input[i] + array_input[j]);
		}
	}
	sort(sum_input.begin(), sum_input.end());
	for(int i = 0; i< sum_input.size();i ++) {
		cout << sum_input[i] << ", ";
	}
	cout << endl;

	int j = array_input.size() -1;
	for (int k = 0; k < array_input.size(); k++ ) { 
		int tmp_target = target - array_input[k];
		int i = k + 1;
		while(i<j) {
			int res = array_input[i] + array_input[j];
			if(res == tmp_target) {
				cout << array_input[k] << ", " << array_input[i] << ", " << array_input[j] << endl;
				i++; j--;
			} else if ( res < target) {
				i++;	
			} else {
				j--;
			}
		}
	}
	return -1;
}

int main() {
	int tmp[] = {1, 2, 3, 3, 4, 5};
	vector<int> array_input(tmp, tmp+6);
	//Get2sum(array_input, 7);
	//Get3sum(array_input, 7);
	Get4sum(array_input, 7);
	return -1;
}

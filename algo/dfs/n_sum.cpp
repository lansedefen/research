#include<vector>
#include<string>
#include<iostream>

using namespace std;

void Get2sumsort(vector<int> arr, int target) {
	int i =0;
	int j = arr.size() -1;
	while(i<j)	{
		if (arr[j] > target - arr[i]) {
			j--;
		} else if (arr[j] == target - arr[i] ) {
			cout << "i:" << i << ", " << " j:" << j << endl;
			i++;	
		} 
		else {
			i++;
		}	
	}
}

void Get3Sum(vector<int>& input, vector<int>& label, vector<int>& res,int index) {
    if (res.size() == 3) {
        int sum_value=0;
        for (int j=0;j < res.size(); j++) {
             sum_value += res[j];
             cout << res[j] << ",";
        }
        if (sum_value == 9) {
            cout << "hit" << endl;
        }
        cout << endl;
    }
    for (int i = 0; i< input.size(); i++) {
        int max_label = -1;
        for (int j = label.size()-1;j>=0;j--) {
            if(label[j] == 1) {
                max_label = j;
                break;
            }
        }

        if (i > max_label) {
            res.push_back(input[i]);
            label[i] = 1;
            Get3Sum(input, label, res, index + 1);
            label[i] = 0;
            res.pop_back();
        }
    }
}

int main() {
	vector<int> arr;
	arr.push_back(1);
	arr.push_back(3);
	arr.push_back(5);
	arr.push_back(8);
	arr.push_back(9);
	arr.push_back(10);
	arr.push_back(16);
	int target = 13;
	Get2sumsort(arr, target);
	return -1;
}

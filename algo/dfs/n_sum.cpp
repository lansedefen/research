#include<vector>
#include<string>
#include<iostream>
#include<numeric>

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

void GetSum(vector<int>& input, vector<int>& label, vector<int>& res, int index) {
    int total = accumulate(res.begin(), res.end(), 0);
    if (total == index) {
        for (int j=0;j < res.size(); j++) {
             cout << res[j] << ",";
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
            GetSum(input, label, res, index);
            label[i] = 0;
            res.pop_back();
        }
    }
}

int main() {
    int input[] = {1,2,3,4,5,8,9};
	vector<int> arr(input, input + 7);
	int target = 13;
    vector<int> label(7, 0);
    vector<int> res;
	GetSum(arr, label, res, target);
	return -1;
}

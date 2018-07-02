#include<vector>
#include<string>
#include<iostream>
using namespace std;

int AdjustVector(vector<int>& input, int start, int end); 

bool FindMaxKNum(vector<int>& input, int start, int end, int k) { 
    int num = AdjustVector(input, start, end);
    cout << "num:" << num << ", start:" << start << ", end:" << end << ", k:" << k <<endl;
    if (num - start == k) {
        return true; 
    }
    else if (num - start < k) {
       cout << "1: num:" << num << ", start:" << num + 1 << ", end:" << end << ", k:" << k + start - num -1 <<endl;
       return FindMaxKNum(input, num + 1, end, k + start - num -1); 
    }
    else {
       cout << "2: num:" << num << ", start:" << start << ", end:" << num-1 << ", k:" << k <<endl;
       return FindMaxKNum(input, start, num-1, k);
    }
}

int FindKMaxNums(vector<int>& nums_first, int first_index, vector<int>& nums_second, int second_index, int k) {
	cout << "first:" << first_index << ", second_index:"<<second_index << ", k:"<< k << endl;
	if (k == 0) {
		return min(nums_first[first_index], nums_second[second_index]);
	} 
	if ((nums_first.size() - first_index == 1) && nums_second.size()-1 >= k) {
		return nums_second[k];
	}
	if ((nums_second.size() - second_index == 1) && nums_first.size()-1 >= k) {
		return nums_first[k];
	}
	if (nums_first.size() - first_index + nums_second.size() - second_index == k - 1) {
		return max(nums_first[first_index], nums_second[second_index]);
	}

	int idx1 = (k -1)/2;
	int idx2 = (k-1) - idx1;
	cout << "idx1:" << idx1 << ", idx2:" << idx2 << endl;
	if (nums_first[first_index + idx1] == nums_second[second_index + idx2]) {
		return nums_first[first_index + idx1];	
	}
	else if(nums_first[first_index + idx1] < nums_second[second_index + idx2]) {
		return FindKMaxNums(nums_first, first_index + idx1 + 1, nums_second, second_index, k - idx1 -1);
	} else {
		return FindKMaxNums(nums_first, first_index, nums_second, second_index + idx2 + 1, k - idx2 -1);
	}
}

int FindMedia(vector<int>& nums_first, vector<int>& nums_second) {
	int m = nums_first.size();
	int n = nums_second.size();
	cout << "m:" << m << ", n:" << n << endl;
	if ((m + n) %2 == 0) {
		return (FindKMaxNums(nums_first, 0, nums_second, 0, (m + n - 1)/2) + FindKMaxNums(nums_first, 0, nums_second, 0, (m + n)/2)  ) /2.0 ; 
	} else {
		return FindKMaxNums(nums_first, 0, nums_second, 0, (m + n)/2); 
	}
	return -1;
}

int AdjustVector(vector<int>& input, int start, int end) {
    for(int i=0;i< input.size(); i++) {
        cout << input[i] << ",";    
    }
    cout << endl;
    int base = input[start];
    int i = start;
    int j = end;
    while (i < j) {
        while (i < j && input[j] > base) {
            j--;
        }
        cout << "j:" << j << ", i:"<< i <<endl;
        if (i<=j) {
            input[i] = input[j];
        }

        for(int k=0; k< input.size(); k++) {
            cout << input[k] << ",";    
        }
        cout << endl;

        while (i<j && input[i] <= base) {
            i++;
        }
        cout << "i:" << i << ", j:"<< j << endl;
        if (i<=j) {
            input[j] = input[i];
        }

        for(int k=0; k< input.size(); k++) {
            cout << input[k] << ",";    
        }
        cout << endl;
    }

    input[i] = base;

    cout << "-----------------" << endl;
    for(int i=0;i< input.size(); i++) {
        cout << input[i] << ",";    
    }
    cout << endl;
    return i;
}

int main() {
	int nums_first[] = {-1, 0, 2, 4};
    vector<int> input_first(nums_first, nums_first + 4);

	int nums_second[] = {1, 3, 4, 5, 6};
    vector<int> input_second(nums_second, nums_second + 5);
 
    //int start = 0;
    //int end = 6;
    // AdjustVector(input, start , end);
    //FindMaxKNum(input, start , end, k);
	int res = FindMedia(input_first, input_second);
	cout << res << endl;
    return -1;
}

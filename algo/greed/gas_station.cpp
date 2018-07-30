#include<iostream>
#include<vector>

using namespace std;

int gasStation(vector<int>& gas, vector<int>& cost) {
	int sum = 0;
	int total = 0;
	int j = 0;
	for(int i =0; i< gas.size(); i++) {
		sum += gas[i] - cost[i];
		total += gas[i] -cost[i];
		if (sum < 0) {
			sum = 0;
			j = i + 1;
		}
	}
	return total >= 0 ? j: -1;
}

int main() {
	vector<int> gas, cost;
	gas.push_back(11);
	gas.push_back(12);
	gas.push_back(13);
	cost.push_back(1);
	cost.push_back(3);
	cost.push_back(4);
	int res = gasStation(gas, cost);
	cout << res << endl;
	return -1;
}

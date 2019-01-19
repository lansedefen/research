#include<iostream>
#include<vector>
#include<string>
#include<queue>
#include <unordered_set>

using namespace std;

unordered_set<string> GetCandidate(string word) {
	unordered_set<string> result;
	for(int i = 0; i < word.size(); i++) {
		for (char c = 'a'; c< 'z'; c++) {
			if (c == word[i]) {
				continue;
			}
			swap(c, word[i]);
			if (1) {
				result.insert(word);
			}
			swap(c, word[i]);
		} 
	}
	return result;
}

int WordPath(string start, string end, unordered_set<string>& dict) {
	unordered_set<string > visited;
	queue<pair<string, int> > q;
	q.push(pair<string ,int >(start, 0 ));

	while(!q.empty()) {
		pair<string, int> top = q.front();
		q.pop();
		if(top.first == end) {
			return 1+ top.second;
		}
		
		cout << "top:" << top.first << endl;
		unordered_set<string> result = GetCandidate(top.first);
		for (unordered_set<string>::iterator i= result.begin(); i != result.end(); i++) {
			if( dict.find(*i) != dict.end() && visited.find(*i) != visited.end() ) {
				cout << "i:" << *i << endl;
				visited.insert(*i);
				q.push(pair<string, int>(*i, 1));
			}
		}
	}
	return -1;
}

int main() {
	string word = "abc";
	unordered_set<string> result = GetCandidate(word);
	for (unordered_set<string>::iterator i = result.begin(); i != result.end(); i++){
            //cout << *i << endl;
	}

	string start = "hit";
	string end = "cog";
	unordered_set<string> dict;
	dict.insert("hot");
	dict.insert("dot");
	dict.insert("dog");
	dict.insert("lot");
	dict.insert("log");
	int res = WordPath(start, end, dict);
	cout << res << endl;
	return -1;
}

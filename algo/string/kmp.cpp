#include<vector>
#include<string>
#include<iostream>

using namespace std;

void GetFail(string pattern, vector<int>& f) {
		f.resize(pattern.size() + 1 , 0);
		for(int i = 1 ; i < pattern.size(); i++) {
		    int j = f[i];
			while(j && pattern[i] != pattern[j]) j = f[j];
			f[i+1] = pattern[i] == pattern[j] ? j+ 1:0;
			cout <<  pattern[i] << ":"<< f[i + 1] << ", ";
		}
        cout << endl << pattern << endl;
}

void KMP(string target, string pattern, vector<int>& f) {
	 int j = 0;
     for (int i =0; i< target.size(); i++) {
	    if (target[i] == pattern[j]) {
				j++;
		} else {
	        j = f[j];
			i -=1;
		}
	    if (j == pattern.size()) {
		   cout << "matched" << endl;
		}
		cout << "i,j:" << i+1 << "("<<target[i+1] << ")"<<", "<<  j<< "("<< pattern[j]<<")"<<endl;
	 }
}

int main() {
   vector<int> f;
   string pattern = "abxxabcd";
   GetFail(pattern, f);
   string target = "abxxabxxabxxabcd";
   cout << "target:" << target << endl;
   KMP(target, pattern, f );
}

